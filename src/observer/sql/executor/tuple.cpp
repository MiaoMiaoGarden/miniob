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

Tuple::Tuple(const Tuple &other) {
    LOG_PANIC("Copy constructor of tuple is not supported");
    exit(1);
}

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

void TupleSchema::add(AttrType type, const char *table_name, const char *field_name, bool isaggre, AggreType agg_type) {
    fields_.emplace_back(type, table_name, field_name, isaggre, agg_type);
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

    // ???????????????????????????????????????
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
        if (iter->isaggre) {
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
        if (iter->isaggre) {
            os << ")";
        }
        os << " | ";
    }

    if (fields_.back().isaggre) {
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
    if (fields_.back().isaggre) {
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

void print_tuples(std::ostream &os, const std::vector<Tuple> &tuples) {
    for (const Tuple &item: tuples) {
        const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
        for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
             iter != end; ++iter) {
            (*iter)->to_string(os);
            os << " | ";
        }
        values.back()->to_string(os);
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
    const RelAttr *groupby_attr = input_schema.get_groupby();
    const char* group_relation_name = input_schema.group_relation_name();
    int groupby_attr_index = -1;
    AttrType groupattr_type = AttrType::UNDEFINED;
    if(groupby_attr!=nullptr){
       groupby_attr_index = output_schema.index_of_field(group_relation_name, groupby_attr->attribute_name);
       groupattr_type = output_schema.field(groupby_attr_index).type();
    }
    int index_num = tuple_fields.size();
    GroupHandler *group_handler = new GroupHandler();
    RC rc = RC::SUCCESS;
    bool count_flag = 0;

    AggregateExeNode agg_exec_node;
    for (auto& tuple : tuple_set.tuples()) {
        Tuple new_tuple;
        int index = 0;
        int group = 0;
        if ( groupby_attr_index!=-1 ){
            TupleValue *tuplevalue = tuple.get_pointer(groupby_attr_index).get();
            group = group_handler->get_group(tuplevalue, groupattr_type);
            if(group<0){
                return RC::GENERIC_ERROR;
            }
        }
        for (auto& tuple_field : tuple_fields) {
            if (tuple_field.aggre_type == AggreType::COUNT && 
                    is_valid_aggre(tuple_field.field_name(), tuple_field.aggre_type)) {
                // ????????????????????????????????? select count(*) from t; ?????????????????????????????????
                // COUNT(*), COUNT(1), ...
                count_flag = 1;
            } else {
                int i = output_schema.index_of_field(tuple_field.table_name(), tuple_field.field_name());
                if (i == -1) {
                    rc = RC::SCHEMA_FIELD_NOT_EXIST;
                    return rc;
                }
                const std::shared_ptr<TupleValue> &value_ptr = tuple.get_pointer(i);
                if (tuple_field.isaggre) {
                    rc = agg_exec_node.add_value(value_ptr, index+group*index_num, tuple_field.aggre_type, tuple_field.type());
                    if (rc != RC::SUCCESS) {
                        return rc;
                    }
                } else {
                    new_tuple.add(value_ptr);
                }
            }
            index += 1;
        }
        if (new_tuple.size() != 0) {
            add(std::move(new_tuple));
        }
    }
    int group_num = 1;
    if(groupby_attr_index!=-1){
        group_num = group_handler->get_group_num(groupattr_type);
    }
    if (agg_exec_node.size() || count_flag) {
        for(int group_id = 0; group_id < group_num; group_id++){
            Tuple new_tuple;
            int index = 0;
            for (auto& tuple_field : tuple_fields) {
                if (tuple_field.aggre_type == AggreType::COUNT && 
            if (tuple_field.aggre_type == AggreType::COUNT && 
                if (tuple_field.aggre_type == AggreType::COUNT && 
                        is_valid_aggre(tuple_field.field_name(), tuple_field.aggre_type)) {
                    std::shared_ptr<TupleValue> value_ptr = std::make_shared<IntValue>(tuple_set.size());
                    new_tuple.add(value_ptr);
                } else {
                    const std::shared_ptr<TupleValue> &value_ptr = agg_exec_node.get_value(index+group_id*index_num);
                    // ??????????????????
                    if (tuple_field.type() == FLOATS && 
                if (tuple_field.type() == FLOATS && 
                    if (tuple_field.type() == FLOATS && 
                            (tuple_field.aggre_type == AggreType::MAX ||
                            tuple_field.aggre_type == AggreType::MIN)) {
                        FloatValue *fvalue_ptr = dynamic_cast<FloatValue *>(value_ptr.get());
                        float value = round(100 * (fvalue_ptr->get_value())) / 100.0;
                        new_tuple.add(value);
                    } else {
                        new_tuple.add(value_ptr);
                    }
                }
                index += 1;
            }
            add(std::move(new_tuple));
        }
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
                const char *s = record + field_meta->offset();  // ????????????Cstring?????????
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


