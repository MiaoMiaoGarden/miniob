#include <memory>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <unordered_map>

#include "execute_stage.h"
#include "common/io/io.h"
#include "common/log/log.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "event/execution_plan_event.h"
#include "sql/executor/execution_node.h"
#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"

bool is_valid_aggre(const char *attr);

class AggregateValue {
public:
    AggregateValue() = default;
    virtual RC add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type, bool count_null) = 0;
    virtual std::shared_ptr<TupleValue> value() = 0;
    virtual ~AggregateValue() {
    }
protected:
};

class AggregateMaxValue : public AggregateValue {
public:
    AggregateMaxValue() = default;
    ~AggregateMaxValue() = default;
    RC add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type, bool count_null) override;
    std::shared_ptr<TupleValue> value() override;
private:
    std::shared_ptr<TupleValue> value_;
};

class AggregateMinValue : public AggregateValue {
public:
    AggregateMinValue() = default;
    ~AggregateMinValue() = default;
    RC add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type, bool count_null) override;
    std::shared_ptr<TupleValue> value() override;
private:
    std::shared_ptr<TupleValue> value_;
};

class AggregateAvgValue : public AggregateValue {
public:
    AggregateAvgValue(): sum(0), count(0), all_null_(true) {
    }
    ~AggregateAvgValue() = default;
    RC add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type, bool count_null) override;
    std::shared_ptr<TupleValue> value() override;
private:
    float sum;
    int count;
    bool all_null_;
};

class AggregateCountValue : public AggregateValue {
public:
    AggregateCountValue(): count(0) {
    }
    ~AggregateCountValue() = default;
    RC add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type, bool count_null) override;
    std::shared_ptr<TupleValue> value() override;
private:
    int count;
};

class AggregateNonValue : public AggregateValue {
public:
    AggregateNonValue(): tuple_value_(nullptr){
    }
    ~AggregateNonValue() = default;
    RC add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type, bool count_null) override;
    std::shared_ptr<TupleValue> value() override;
private:
    std::shared_ptr<TupleValue> tuple_value_;
};

class AggregateExeNode {
public:
    AggregateExeNode() = default;
    ~AggregateExeNode() = default;
    
    RC add_value(const std::shared_ptr<TupleValue> &tuple_value, int index, 
                    AggreType agg_type, AttrType attr_type, bool count_null) {
        AggregateValue* value = record_map[index].get();
        if (value == nullptr) {
            if (agg_type == COUNT) {
                value = new AggregateCountValue();
            } else if (agg_type == MIN) {
                value = new AggregateMinValue();
            } else if (agg_type == MAX) {
                value = new AggregateMaxValue();
            } else if (agg_type == AVG) {
                value = new AggregateAvgValue();
            } else if ( agg_type == NON ) {
                value = new AggregateNonValue();
            }
            record_map[index].reset(value);
        }
        return value->add(tuple_value, attr_type, count_null);
    }

    std::shared_ptr<TupleValue> get_value(int index) {
        if (record_map.size() == 0) return nullptr;
        return record_map[index]->value();
    }

    size_t size() {
        return record_map.size();
    }
private:
    std::unordered_map<int, std::unique_ptr<AggregateValue>> record_map;
};

class GroupHandler {
public:
    GroupHandler() = default;
    ~GroupHandler() = default;
    int get_group(const Tuple &tuple, const std::vector<RelAttr> &groupby_attr, const TupleSchema &output_schema){
        // Tuple *new_tupe = std::move(tuple);
        int hashed = 0;
        for(auto &groupby : groupby_attr){
            int index = output_schema.index_of_field(groupby.relation_name, groupby.attribute_name);
            // const TupleValue & tuple_value = tuple.get(index);
            // TupleValue *tuple_value_addr = const_cast<TupleValue*>(&tuple_value);

            // std::string value = (dynamic_cast<StringValue*>(tuple_value_addr))->get_string_value();
            std::string value = tuple.get(index).get_string_value();
            hashed += hash_fn(value);
        }
        if(string_group_map.find(hashed)==string_group_map.end()){
            string_group_map[hashed] = string_group_map.size();
        }
        return string_group_map[hashed];
    }

    size_t get_group_num(){
       return string_group_map.size();
    }
private:
    std::unordered_map<int, int> string_group_map;
    std::hash<std::string> hash_fn;
protected:
};

/*
    do_aggregate(const Selects &selects, TupleSet &tuple_set, TupleSet &aggred_tupleset) {
        Tuple aggred_tuple;
        for(size_t i = 0; i < selects.attr_num; i++) {
          RelAttr attr = selects.attributes[selects.attr_num - 1 - i];
          int index = 0;
          char parsed[100];
          bool count_null = false;
          parse_attr(attr.attribute_name, attr.aggre_type, parsed);
          if(attr.aggre_type != NON && is_valid_aggre(parsed, attr.aggre_type)){  // count(1)\ count(*)\ etc..
              index = 0;
              count_null = true;
           } else {
             index = tuple_set.get_schema().index_of_field(selects.relations[0], parsed);
             count_null = false;
          }
          if (attr.aggre_type == COUNT){
            if(count_null) {
              aggred_tuple.add(tuple_set.size());
            } else {
              // null check here
                int count = 0;
                for(auto &temp1:tuple_set.tuples()){
                  if(temp1.get(index).is_null()) continue;
                  else count++;
                }
                aggred_tuple.add(count);
            }
          } else if(attr.aggre_type == MIN){
            int min_index = 0;
            while(min_index < tuple_set.size() && (tuple_set.get(min_index).get(index).is_null())){
              min_index++;
            }
            for(size_t j = min_index + 1; j < tuple_set.size(); j++){
              if(tuple_set.get(j).get(index).is_null()) continue;
              if(tuple_set.get(min_index).get(index).compare(tuple_set.get(j).get(index)) > 0){
                min_index = j;
              }
            }
            int t1 = 0;
            bool flag = false;
            for (auto &temp1: tuple_set.tuples()) {
                int t2 = 0;
                for (auto &value: temp1.values()) {
                    if (t1 == min_index && t2 == index) {
                        if (tuple_set.get_schema().field(index).type() == FLOATS) {
                            FloatValue *floatvalue = dynamic_cast<FloatValue *>(value.get());
                            float fvalue = round(100 * (floatvalue->get_value())) / 100.0;
                            aggred_tuple.add(fvalue);
                        } else {
                            aggred_tuple.add(value);
                        }
                        flag = true;
                        break;
                    }
                    t2++;
                }
                if (flag) break;
                t1++;
            }
        } else if (attr.aggre_type == MAX) {
            int max_index = 0;
            while(max_index<tuple_set.size() && (tuple_set.get(max_index).get(index).is_null())){
              max_index++;
            }
            for(size_t j = max_index + 1; j < tuple_set.size(); j++){
              if(tuple_set.get(j).get(index).is_null()) continue;
              if(tuple_set.get(max_index).get(index).compare(tuple_set.get(j).get(index)) < 0){
                max_index = j;
              }
            }
            int t1 = 0;
            bool flag = false;
            for (auto &temp1: tuple_set.tuples()) {
                int t2 = 0;
                for (auto &value: temp1.values()) {
                    if (t1 == max_index && t2 == index) {
                        if (tuple_set.get_schema().field(index).type() == FLOATS) {
                            FloatValue *floatvalue = dynamic_cast<FloatValue *>(value.get());
                            float fvalue = round(100 * (floatvalue->get_value())) / 100.0;
                            aggred_tuple.add(fvalue);
                        } else {
                            aggred_tuple.add(value);
                        }

                        flag = true;
                        break;
                    }
                    t2++;
                }
                if (flag) break;
                t1++;
            }
        } else if (attr.aggre_type == AVG) {
            AttrType type = tuple_set.get_schema().field(index).type();
            if (type != FLOATS && type != INTS) {
                return RC::GENERIC_ERROR;
            }
            if(type == FLOATS){
                float sum  = 0.0;
                int count = 0;
                for(auto &temp1:tuple_set.tuples()){
                  if(temp1.get(index).is_null()) continue;
                  int t2 = 0;
                  for(auto &value : temp1.values()){
                    if(t2==index){
                        count++;
                        FloatValue *floatvalue = dynamic_cast<FloatValue *>(value.get());
                        sum+=floatvalue->get_value();
                        break;  // changed here directly
                    }
                  }
                }
                float avg = round(100 * sum / tuple_set.size()) / 100.0;
                aggred_tuple.add(avg);

            }
            if (type == INTS) {
                int sum = 0;
                int count = 0;
                for(auto &temp1:tuple_set.tuples()){
                  if(temp1.get(index).is_null()) continue;
                  int t2 = 0;
                  for(auto &value : temp1.values()){
                    if(t2==index){
                        count++;
                        IntValue *intvalue = dynamic_cast<IntValue *>(value.get());
                        sum+=intvalue->get_value();
                        break;
                    }
                  }
                }
                float avg = round(100*(float)sum/count)/100.0;
                aggred_tuple.add(avg);
            }
        }

    }
    aggred_tupleset.add(std::move(aggred_tuple));
    return RC::SUCCESS;
}

private:

}; */
