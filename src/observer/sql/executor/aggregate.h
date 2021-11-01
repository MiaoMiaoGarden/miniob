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

bool is_valid_aggre(const char *attr, AggreType aggre_type);
void parse_attr(char *attribute_name, AggreType aggre_type, char *attr_name);

class AggregateValue {
public:
    AggregateValue() = default;
    virtual RC add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type) = 0;
    virtual std::shared_ptr<TupleValue> value() = 0;
    virtual ~AggregateValue();
protected:
};

class AggregateMaxValue : public AggregateValue {
public:
    AggregateMaxValue() = default;
    ~AggregateMaxValue() = default;
    RC add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type) override;
    std::shared_ptr<TupleValue> value() override;
private:
    std::shared_ptr<TupleValue> value_;
};

class AggregateMinValue : public AggregateValue {
public:
    AggregateMinValue() = default;
    ~AggregateMinValue() = default;
    RC add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type) override;
    std::shared_ptr<TupleValue> value() override;
private:
    std::shared_ptr<TupleValue> value_;
};

class AggregateAvgValue : public AggregateValue {
public:
    AggregateAvgValue(): sum(0), count(0) {
    }
    ~AggregateAvgValue() = default;
    RC add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type) override;
    std::shared_ptr<TupleValue> value() override;
private:
    float sum;
    int count;
};

class AggregateCountValue : public AggregateValue {
public:
    AggregateCountValue(): count(0) {
    }
    ~AggregateCountValue() = default;
    RC add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type) override;
    std::shared_ptr<TupleValue> value() override;
private:
    int count;
};

class AggregateExeNode {
public:
    AggregateExeNode();
    ~AggregateExeNode();
    
    void add_value(const std::shared_ptr<TupleValue> &tuple_value, const char* table_name, 
            const char* attr_name, AggreType agg_type, AttrType attr_type) {
        std::string record_name(table_name);
        record_name += attr_name;
        AggregateValue* value = record_map[record_name].get();
        if (value == nullptr) {
            if (agg_type == COUNT) {
                value = new AggregateCountValue();
            } else if (agg_type == MIN) {
                value = new AggregateMinValue();
            } else if (agg_type == MAX) {
                value = new AggregateMaxValue();
            } else if (agg_type == AVG) {
                value = new AggregateAvgValue();
            }
            record_map[record_name].reset(value);
        }
        value->add(tuple_value, attr_type);
    }

    std::shared_ptr<TupleValue> get_value(const char* table_name, const char* attr_name) {
        std::string record_name(table_name);
        record_name += attr_name;
        return record_map[record_name]->value();
    }
private:
    std::unordered_map<std::string, std::unique_ptr<AggregateValue>> record_map;
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
