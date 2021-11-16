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
// Created by Wangyunlai on 2021/5/7.
//

#include <stddef.h>
#include <sstream>
#include "condition_filter.h"
#include "record_manager.h"
#include "common/log/log.h"
#include "storage/common/table.h"

using namespace common;

ConditionFilter::~ConditionFilter() {}

DefaultConditionFilter::DefaultConditionFilter() {
    left_.is_attr = false;
    left_.attr_length = 0;
    left_.attr_offset = 0;
    left_.value = nullptr;

    right_.is_attr = false;
    right_.attr_length = 0;
    right_.attr_offset = 0;
    right_.value = nullptr;
}

DefaultConditionFilter::~DefaultConditionFilter() {}

RC DefaultConditionFilter::init(const ConDesc &left, const ConDesc &right, AttrType left_attr_type, AttrType right_attr_type, CompOp comp_op) {
    if ((left_attr_type < CHARS || left_attr_type > NULLS) || (right_attr_type < CHARS || right_attr_type > NULLS)) {
        LOG_ERROR("Invalid condition with unsupported attribute type: %d, %d", left_attr_type, right_attr_type);
        return RC::INVALID_ARGUMENT;
    }

    if (comp_op < EQUAL_TO || comp_op > NOTIN_COMPOP || comp_op == NO_OP) {
        LOG_ERROR("Invalid condition with unsupported compare operation: %d", comp_op);
        return RC::INVALID_ARGUMENT;
    }

    left_ = left;
    right_ = right;
    left_attr_type_ = left_attr_type;
    right_attr_type_ = right_attr_type;
    comp_op_ = comp_op;
    return RC::SUCCESS;
}

RC DefaultConditionFilter::init(Table &table, const Condition &condition) {
    const TableMeta &table_meta = table.table_meta();
    ConDesc left;
    left.value_tuple_size = 0;
    ConDesc right;
    right.value_tuple_size = 0;

    AttrType type_left = UNDEFINED;
    AttrType type_right = UNDEFINED;

    if (ATTR == condition.left_type) {
        left.is_attr = true;
        const FieldMeta *field_left = table_meta.field(condition.left_attr.attribute_name);
        if (nullptr == field_left) {
            LOG_WARN("No such field in condition. %s.%s", table.name(), condition.left_attr.attribute_name);
            return RC::SCHEMA_FIELD_MISSING;
        }
        left.attr_length = field_left->len();
        left.attr_offset = field_left->offset();

        left.value = nullptr;
        left.nullable = field_left->nullable();

        type_left = field_left->type();
    } else {
        type_left = condition.left_value.type;
        left.is_attr = false;
        if (condition.left_value.type == NULLS) {
            type_left = NULLS;
        } else if (condition.left_value.data != nullptr){
            left.value = condition.left_value.data;
            char *left_value = (char *) (left.value);
            if (*left_value == '!') {
                type_left = NULLS;
            }
        } else if (condition.left_value.tuple_data_size != 0){
            left.value = nullptr;
            for(int i = 0; i < condition.left_value.tuple_data_size; i++) {
                left.value_tuple[left.value_tuple_size++] = condition.left_value.tuple_data[i];
            }
        } else {
            return RC::EMPTY;
        }

        left.attr_length = 0;
        left.attr_offset = 0;
    }

    if (ATTR == condition.right_type) {
        right.is_attr = true;
        const FieldMeta *field_right = table_meta.field(condition.right_attr.attribute_name);
        if (nullptr == field_right) {
            LOG_WARN("No such field in condition. %s.%s", table.name(), condition.right_attr.attribute_name);
            return RC::SCHEMA_FIELD_MISSING;
        }
        right.attr_length = field_right->len();
        right.attr_offset = field_right->offset();
        type_right = field_right->type();
        right.nullable = field_right->nullable();

        right.value = nullptr;
    } else {
        right.is_attr = false;
        type_right = condition.right_value.type;
        if (condition.right_value.type == NULLS) {
            type_right = NULLS;
        } else if (condition.right_value.data != nullptr){
            right.value = condition.right_value.data;
            char *right_value = (char *) (right.value);
            if (*right_value == '!') {
                type_right = NULLS;
            }
        } else if (condition.right_value.tuple_data_size != 0){
            right.value = nullptr;
            for(int i = 0; i < condition.right_value.tuple_data_size; i++) {
                right.value_tuple[right.value_tuple_size++] = condition.right_value.tuple_data[i];
            }
        } else {
            return RC::EMPTY;
        }

        right.attr_length = 0;
        right.attr_offset = 0;
    }

    // 校验和转换
    //  if (!field_type_compare_compatible_table[type_left][type_right]) {
    //    // 不能比较的两个字段， 要把信息传给客户端
    //    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    //  }
    // NOTE：这里没有实现不同类型的数据比较，比如整数跟浮点数之间的对比
    // 但是选手们还是要实现。这个功能在预选赛中会出现
    if ((type_left != type_right) && ((type_left != FLOATS && type_left != INTS) || (type_right != FLOATS && type_right != INTS)) && (type_left != NULLS && type_right != NULLS)) {  // both are not null, and unmatch
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }

    return init(left, right, type_left, type_right, condition.comp);
}

std::vector<std::string> split_(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(std::move(item)); // in C++11 (based on comment from @mchiasson)
    }
    return elems;
}

bool DefaultConditionFilter::filter(const Record &rec) const {
    if (!left_.is_attr) {
        if (comp_op_ == IN_COMPOP) {
            bool ans = false;
            if (left_.value != nullptr || left_attr_type_ == NULLS) {
                ans = filter_composed(rec, IS_COMPOP, nullptr, nullptr);
            } else {
                for (int i = 0; i < left_.value_tuple_size; i++) {
                    if (filter_composed(rec, IS_COMPOP, left_.value_tuple[i], nullptr)) {
                        ans = true;
                        break;
                    }
                }
            }
            return ans;
        }
        else if (comp_op_ == NOTIN_COMPOP) {
            bool ans = true;
            if (left_.value != nullptr || left_attr_type_ == NULLS) {
                ans = filter_composed(rec, IS_NOT_COMPOP, nullptr, nullptr);
            } else {
                for (int i = 0; i < left_.value_tuple_size; i++) {
                    if (filter_composed(rec, IS_COMPOP, left_.value_tuple[i], nullptr)) {
                        ans = false;
                        break;
                    }
                }
            }
            return ans;
        } 
    }

    if (!right_.is_attr) {
        if (comp_op_ == IN_COMPOP) {
            bool ans = false;
            if (right_.value != nullptr || right_attr_type_ == NULLS) {
                ans = filter_composed(rec, IS_COMPOP, nullptr, nullptr);
            } else {
                for (int i = 0; i < right_.value_tuple_size; i++) {
                    if (filter_composed(rec, IS_COMPOP, nullptr, right_.value_tuple[i])) {
                        ans = true;
                        break;
                    }
                }
            }
            return ans;
        }
        else if (comp_op_ == NOTIN_COMPOP) {
            bool ans = true;
            if (right_.value != nullptr || right_attr_type_ == NULLS) {
                ans = filter_composed(rec, IS_NOT_COMPOP, nullptr, nullptr);
            } else {
                for (int i = 0; i < right_.value_tuple_size; i++) {
                    if (filter_composed(rec, IS_COMPOP, nullptr, right_.value_tuple[i])) {
                        ans = false;
                        break;
                    }
                }
            }
            return ans;
        } 
    }

    return filter_composed(rec, comp_op_, nullptr, nullptr);
}

bool DefaultConditionFilter::filter_composed(const Record &rec, CompOp comp_op, void* left_composed_value, void *right_composed_value) const {
    char *left_value = nullptr;
    char *right_value = nullptr;

    if (left_.is_attr) {  // value
        left_value = (char *) (rec.data + left_.attr_offset);
    } else if (left_composed_value) {
        left_value = (char *) left_composed_value;
    } else {
        left_value = (char *) left_.value;
    }

    if (right_.is_attr) {
        right_value = (char *) (rec.data + right_.attr_offset);
    } else if (right_composed_value) {
        right_value = (char *) right_composed_value;
    } else {
        right_value = (char *) right_.value;
    }

    float cmp_result = 0;  // 0 false, 1 true
    bool left_is_null = (*left_value == '!') || left_attr_type_ == NULLS;
    bool right_is_null = (*right_value == '!') || right_attr_type_ == NULLS;

    if (left_is_null && right_is_null) {  // null comop null
        if (comp_op == IS_COMPOP) {   // is
            return true;
        } else if (comp_op == IS_NOT_COMPOP) {   // is not
            return false;
        } else {     // >=、noop
            return false;
        }
    } else if (left_is_null) {  // null comop (value/id,anything not null)
        if (comp_op <= 7) {  // >=、noop
            return false;
        } else if (comp_op == IS_COMPOP) { // is
            return false;
        } else if (comp_op == IS_NOT_COMPOP) {  // is not
            return true;
        } else {
            LOG_PANIC("Never should print this.");
        }
    } else if (right_is_null) {   // (value/id,anything not null) compop null
        if (comp_op <= 7) {  // >=、noop
            return false;
        } else if (comp_op == IS_COMPOP) {  // is
            return false;
        } else if (comp_op == IS_NOT_COMPOP) { // isnot
            return true;
        } else {
            LOG_PANIC("Never should print this.");
        }
    } else {  // notnull comop notnull
        switch (left_attr_type_) {  // left.attr_type
            case CHARS:
            case TEXTS: {  // 字符串都是定长的，直接比较
                // 按照C字符串风格来定
                cmp_result = strcmp(left_value, right_value);
            }
                break;
            case INTS: {
                // 没有考虑大小端问题
                // 对int和float，要考虑字节对齐问题,有些平台下直接转换可能会跪
                if (right_attr_type_ == INTS) {
                    int left = *(int *) left_value;
                    int right = *(int *) right_value;
                    cmp_result = left - right;
                } else {
                    int left = *(int *) left_value;
                    float right = *(float *) right_value;
                    cmp_result = left - right;
                }
            }
                break;
            case FLOATS: {
                if (right_attr_type_ == FLOATS) {
                    float left = *(float *) left_value;
                    float right = *(float *) right_value;
                    cmp_result = left - right;
                } else {
                    float left = *(float *) left_value;
                    int right = *(int *) right_value;
                    cmp_result = left - right;
                }      
            }
                break;
            case DATES: {
                int left = *(int *) left_value;
                int right = *(int *) right_value;
                cmp_result = left - right;
            }
                break;
            default: {
            }
        }
        switch (comp_op) {
            case EQUAL_TO:
                return 0 == cmp_result;
            case LESS_EQUAL:
                return cmp_result <= 0;
            case NOT_EQUAL:
                return cmp_result != 0;
            case LESS_THAN:
                return cmp_result < 0;
            case GREAT_EQUAL:
                return cmp_result >= 0;
            case GREAT_THAN:
                return cmp_result > 0;
            case IS_COMPOP:
                return 0 == cmp_result;
            case IS_NOT_COMPOP:
                return cmp_result != 0;  // TODO: 1 is 1 return what?
            default:
                break;
        }
    }

    LOG_PANIC("Never should print this.");
    return cmp_result;  // should not go here
}

CompositeConditionFilter::~CompositeConditionFilter() {
    if (memory_owner_) {
        delete[] filters_;
        filters_ = nullptr;
    }
}

RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num, bool own_memory) {
    filters_ = filters;
    filter_num_ = filter_num;
    memory_owner_ = own_memory;
    return RC::SUCCESS;
}

RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num) {
    return init(filters, filter_num, false);
}

RC CompositeConditionFilter::init(Table &table, const Condition *conditions, int condition_num) {
    if (condition_num == 0) {
        return RC::SUCCESS;
    }
    if (conditions == nullptr) {
        return RC::INVALID_ARGUMENT;
    }

    RC rc = RC::SUCCESS;
    ConditionFilter **condition_filters = new ConditionFilter *[condition_num];
    for (int i = 0; i < condition_num; i++) {
        DefaultConditionFilter *default_condition_filter = new DefaultConditionFilter();
        rc = default_condition_filter->init(table, conditions[i]);
        if (rc != RC::SUCCESS) {
            delete default_condition_filter;
            for (int j = i - 1; j >= 0; j--) {
                delete condition_filters[j];
                condition_filters[j] = nullptr;
            }
            delete[] condition_filters;
            condition_filters = nullptr;
            return rc;
        }
        condition_filters[i] = default_condition_filter;
    }
    return init((const ConditionFilter **) condition_filters, condition_num, true);
}

bool CompositeConditionFilter::filter_composed(const Record &rec, CompOp comp_op, void* left_composed_value, void *right_composed_value) const {
    for (int i = 0; i < filter_num_; i++) {
        if (!filters_[i]->filter(rec)) {
            return false;
        }
    }
    return true;
}

bool CompositeConditionFilter::filter(const Record &rec) const {
    return filter_composed(rec, NO_OP, nullptr, nullptr);
}
