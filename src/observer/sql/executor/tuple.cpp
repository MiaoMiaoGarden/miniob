/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/14.
//

#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "common/log/log.h"
#include "sql/executor/aggregate.h"
#include <memory>

/*
Tuple::Tuple(const Tuple &other) {
    LOG_PANIC("Copy constructor of tuple is not supported");
    exit(1);
}
*/

Tuple::Tuple(Tuple &&other) noexcept: values_(std::move(other.values_)) {
}

Tuple &Tuple::operator=(Tuple &&other) noexcept {
    if (&other == this) {
        return *this;
    }

    values_.clear();
    values_.swap(other.values_);
    return *this;
}

Tuple::~Tuple() {
}

// add (Value && value)
void Tuple::add(TupleValue *value) {
    values_.emplace_back(value);
}

void Tuple::add(const std::shared_ptr<TupleValue> &other) {
    values_.emplace_back(other);
}

void Tuple::add(int value) {
    add(new IntValue(value));
}

void Tuple::add(float value) {
    add(new FloatValue(value));
}

void Tuple::add(const char *s, int len) {
    add(new StringValue(s, len));
}

void Tuple::add(int value, bool flag) {
    if (flag)
        add(new DateValue(value));
}

////////////////////////////////////////////////////////////////////////////////

std::string TupleField::to_string() const {
    return std::string(table_name_) + "." + field_name_ + std::to_string(type_);
}

////////////////////////////////////////////////////////////////////////////////
void TupleSchema::from_table(const Table *table, TupleSchema &schema) {
    const char *table_name = table->name();
    const TableMeta &table_meta = table->table_meta();
    const int field_num = table_meta.field_num();
    for (int i = 0; i < field_num; i++) {
        const FieldMeta *field_meta = table_meta.field(i);
        if (field_meta->visible()) {
            schema.add(field_meta->type(), table_name, field_meta->name());
        }
    }
}

void TupleSchema::add(AttrType type, const char *table_name, const char *field_name) {
    fields_.emplace_back(type, table_name, field_name);
}

void TupleSchema::add(AttrType type, const char *table_name, const char *field_name, AggreType agg_type) {
    fields_.emplace_back(type, table_name, field_name, agg_type);
}


void TupleSchema::add_if_not_exists(AttrType type, const char *table_name, const char *field_name) {
    for (const auto &field: fields_) {   // todo: aggre & no aggre need to check here
        if (0 == strcmp(field.table_name(), table_name) &&
            0 == strcmp(field.field_name(), field_name)) {
            return;
        }
    }
    add(type, table_name, field_name);
}

void TupleSchema::append(const TupleSchema &other) {
    fields_.reserve(fields_.size() + other.fields_.size());
    for (const auto &field: other.fields_) {
        fields_.emplace_back(field);
    }
}

int TupleSchema::index_of_field(const char *table_name, const char *field_name) const {
    const int size = fields_.size();
    for (int i = 0; i < size; i++) {
        const TupleField &field = fields_[i];
        if (0 == strcmp(field.table_name(), table_name) && 0 == strcmp(field.field_name(), field_name)) {
            return i;
        }
    }
    return -1;
}

void TupleSchema::print(std::ostream &os) const {
    if (fields_.empty()) {
        os << "No schema";
        return;
    }

    // 判断有多张表还是只有一张表
    std::set<std::string> table_names;
    for (const auto &field: fields_) {
        table_names.insert(field.table_name());
    }

    for (std::vector<TupleField>::const_iterator iter = fields_.begin(), end = --fields_.end();
         iter != end; ++iter) {
        if (table_names.size() > 1) {
            os << iter->table_name() << ".";
        }
        os << iter->field_name() << " | ";
    }

    if (table_names.size() > 1) {
        os << fields_.back().table_name() << ".";
    }
    os << fields_.back().field_name() << std::endl;
}

void TupleSchema::print(std::ostream &os, bool flag) const {
    if (fields_.empty()) {
        os << "No schema";
        return;
    }

    for (std::vector<TupleField>::const_iterator iter = fields_.begin(), end = --fields_.end();
         iter != end; ++iter) {
        if (iter->aggre_type!=AggreType::NON) {
            if (iter->aggre_type == AggreType::MIN) {
                os << "min(";
            } else if (iter->aggre_type == AggreType::MAX) {
                os << "max(";
            } else if (iter->aggre_type == AggreType::AVG) {
                os << "avg(";
            } else if (iter->aggre_type == AggreType::COUNT) {
                os << "count(";
            }
        }
        if (flag) {
            os << iter->table_name() << ".";
        }
        os << iter->field_name();
        if (iter->aggre_type!=AggreType::NON) {
            os << ")";
        }
        os << " | ";
    }

    if (fields_.back().aggre_type != AggreType::NON) {
        if (fields_.back().aggre_type == AggreType::MIN) {
            os << "min(";
        } else if (fields_.back().aggre_type == AggreType::MAX) {
            os << "max(";
        } else if (fields_.back().aggre_type == AggreType::AVG) {
            os << "avg(";
        } else if (fields_.back().aggre_type == AggreType::COUNT) {
            os << "count(";
        }
    }

    if (flag) {
        os << fields_.back().table_name() << ".";
    }
    os << fields_.back().field_name();
    if (fields_.back().aggre_type != AggreType::NON) {
        os << ")";
    }

    os << std::endl;
}

void TupleSchema::print_with_tablename(std::ostream &os) const {
    if (fields_.empty()) {
        os << "No schema";
        return;
    }

    for (std::vector<TupleField>::const_iterator iter = fields_.begin(), end = --fields_.end();
         iter != end; ++iter) {
        os << iter->table_name() << ".";
        os << iter->field_name() << " | ";
    }

    os << fields_.back().table_name() << ".";
    os << fields_.back().field_name() << std::endl;
}

/////////////////////////////////////////////////////////////////////////////
bool is_float_output(AttrType attr_type, AggreType aggre_type){
    if ( attr_type == AttrType::FLOATS ){
        return true;
    }
    if ( aggre_type == AggreType::AVG ){
        return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////
TupleSet::TupleSet(TupleSet &&other) : tuples_(std::move(other.tuples_)), schema_(other.schema_) {
    other.schema_.clear();
}

TupleSet &TupleSet::operator=(TupleSet &&other) {
    if (this == &other) {
        return *this;
    }

    schema_.clear();
    schema_.append(other.schema_);
    other.schema_.clear();

    tuples_.clear();
    tuples_.swap(other.tuples_);
    return *this;
}

void TupleSet::add(Tuple &&tuple) {
    tuples_.emplace_back(std::move(tuple));
}

void TupleSet::clear() {
    tuples_.clear();
    schema_.clear();
}

RC TupleSet::sort(const Selects &selects) {
    RC rc = RC::SUCCESS;
    const TupleSchema &schema = this->get_schema();
    auto compare = [&schema, &selects, &rc](const Tuple& tuple1, const Tuple& tuple2) -> bool {
        if (rc != RC::SUCCESS) {
            return true;
        }
        for (int i = 0; i < selects.orderbys_num; i++) {
            const Orderby& orderby = selects.orderbys[i];
            const char* table_name = orderby.attr.relation_name;
            const char* attribute_name = orderby.attr.attribute_name;
            if (table_name == nullptr) {
                table_name = selects.relations[0];
            }
            int idx = schema.index_of_field(table_name, attribute_name);
            if (idx == -1) {
                rc = RC::SCHEMA_FIELD_NAME_ILLEGAL;
                return false;
            }
            int result = tuple1.get(idx).compare(tuple2.get(idx));
            if (result == -1) {
                return orderby.asc_desc == OrderType::O_AES;
            }
            if (result == 1) {
                return orderby.asc_desc == OrderType::O_DESC;
            }
        }
        return true;
    };
    std::sort(this->tuples_.begin(), this->tuples_.end(), compare);
    return rc;
}

void print_tuples(std::ostream &os, const std::vector<Tuple> &tuples) {
    for (const Tuple &item: tuples) {
        const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
        for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
             iter != end; ++iter) {
            (*iter)->to_string(os);
            os << " | ";
        }
        if(values.back().get() == nullptr){
            os << "null";
        } else {
            values.back()->to_string(os);
        }
        os << std::endl;
    }
}

void TupleSet::print_with_tablename(std::ostream &os) const {
    if (schema_.fields().empty()) {
        LOG_WARN("Got empty schema");
        return;
    }

    schema_.print_with_tablename(os);
    print_tuples(os, tuples_);
}

void TupleSet::print(std::ostream &os) const {
    if (schema_.fields().empty()) {
        LOG_WARN("Got empty schema");
        return;
    }

    schema_.print(os);
    print_tuples(os, tuples_);
}

void TupleSet::print(std::ostream &os, bool flag) const {
    if (schema_.fields().empty()) {
        LOG_WARN("Got empty schema");
        return;
    }

    schema_.print(os, flag);
    print_tuples(os, tuples_);
}

void TupleSet::set_schema(const TupleSchema &schema) {
    schema_ = schema;
}  

RC TupleSet::set_tuple_set(TupleSet &&tuple_set) {
    const TupleSchema &output_schema = tuple_set.schema();
    const TupleSchema &input_schema = this->schema();
    const std::vector<TupleField> &tuple_fields = input_schema.fields();
    RC rc = RC::SUCCESS;
    
    int index_num = tuple_fields.size();
    std::vector<bool> field_count_null;

    bool select_isaggre = false;
    
    for (auto &field : tuple_fields) {
        if (field.aggre_type == AggreType::COUNT && is_valid_aggre(field.field_name())){
            field_count_null.push_back(true);
        } else {
            field_count_null.push_back(false);
        }
        if (field.aggre_type != AggreType::NON){
            select_isaggre = true;
        }
    }
    
    // not aggregate selection, return immediately
    if (!select_isaggre){
        for (auto& tuple : tuple_set.tuples()) {
            Tuple new_tuple;
            for (auto& tuple_field : tuple_fields){
                int i = output_schema.index_of_field(tuple_field.table_name(), tuple_field.field_name());
                if (i == -1) {
                    rc = RC::SCHEMA_FIELD_NOT_EXIST;
                    return rc;
                }
                const std::shared_ptr<TupleValue> &value_ptr = tuple.get_pointer(i);
                new_tuple.add(value_ptr);
            }
            add(std::move(new_tuple));
        }
        return RC::SUCCESS;
    }

    // need to aggregate
    //   init groupby
    const std::vector<RelAttr> &groupby_attr  = input_schema.get_groupby();
    const int groupby_num = input_schema.get_groupby_num();
    GroupHandler *group_handler = new GroupHandler();

    AggregateExeNode agg_exec_node;

    // group and aggregate
    for (auto& tuple : tuple_set.tuples()) {
        Tuple new_tuple;
        int group = 0;
        if ( groupby_num > 0){ 
            group = group_handler->get_group(tuple,groupby_attr, output_schema);
            if(group<0){
                return RC::GENERIC_ERROR;
            }
        }
        int index = 0;
        for (auto& tuple_field : tuple_fields) {
            int i = output_schema.index_of_field(tuple_field.table_name(), tuple_field.field_name());
            if(is_valid_aggre(tuple_field.field_name())) {
                i = 0;
            }
            if (i == -1) {
                rc = RC::SCHEMA_FIELD_NOT_EXIST;
                return rc;
            }
            const std::shared_ptr<TupleValue> &value_ptr = tuple.get_pointer(i);
            rc = agg_exec_node.add_value(value_ptr, index+group*index_num, tuple_field.aggre_type, tuple_field.type(),field_count_null[index]);
            if (rc != RC::SUCCESS) {
                return rc;
            }
            index += 1;
        }
    }

    // get aggregated data
    int group_num = 1;
    if(groupby_num>0){
        group_num = group_handler->get_group_num();
    }
    for(int group_id = 0; group_id < group_num; group_id++){
        Tuple new_tuple;
        int index = 0;
        for (auto& tuple_field : tuple_fields) {
            const std::shared_ptr<TupleValue> &value_ptr = agg_exec_node.get_value(index+group_id*index_num);
                // 处理精度问题
            if (value_ptr == nullptr){
                new_tuple.add(nullptr);
            } else if (is_float_output(tuple_field.type(), tuple_field.aggre_type)) {
                    FloatValue *fvalue_ptr = dynamic_cast<FloatValue *>(value_ptr.get());
                    float value = round(100 * (fvalue_ptr->get_value())) / 100.0;
                    new_tuple.add(value);
            } else {
                new_tuple.add(value_ptr);
            }
            index += 1;  
        }
        add(std::move(new_tuple));
    }
    return rc;
}

const TupleSchema &TupleSet::get_schema() const {
    return schema_;
}

bool TupleSet::is_empty() const {
    return tuples_.empty();
}

int TupleSet::size() const {
    return tuples_.size();
}

const Tuple &TupleSet::get(int index) const {
    return tuples_[index];
}

const std::vector<Tuple> &TupleSet::tuples() const {
    return tuples_;
}

/////////////////////////////////////////////////////////////////////////////
TupleRecordConverter::TupleRecordConverter(Table *table, TupleSet &tuple_set) :
        table_(table), tuple_set_(tuple_set) {
}

void TupleRecordConverter::add_record(const char *record) {
    const TupleSchema &schema = tuple_set_.schema();
    Tuple tuple;
    const TableMeta &table_meta = table_->table_meta();
    for (const TupleField &field: schema.fields()) {
        const FieldMeta *field_meta = table_meta.field(field.field_name());
        assert(field_meta != nullptr);
        switch (field_meta->type()) {
            case INTS: {
                int value = *(int *) (record + field_meta->offset());
                tuple.add(value);
            }
                break;
            case FLOATS: {
                float value = *(float *) (record + field_meta->offset());
                tuple.add(value);
            }
                break;
            case CHARS: {
                const char *s = record + field_meta->offset();  // 现在当做Cstring来处理
                tuple.add(s, strlen(s));
            }
                break;
            case DATES: {
                int value = *(int *) (record + field_meta->offset());
                tuple.add(value, true);
            }
                break;
            default: {
                LOG_PANIC("Unsupported field type. type=%d", field_meta->type());
            }
        }
    }
    if (tuple.size() != 0)
        tuple_set_.add(std::move(tuple));
}

