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

ConditionFilter::~ConditionFilter()
{}

DefaultConditionFilter::DefaultConditionFilter()
{
  left_.is_attr = false;
  left_.attr_length = 0;
  left_.attr_offset = 0;
  left_.value = nullptr;

  right_.is_attr = false;
  right_.attr_length = 0;
  right_.attr_offset = 0;
  right_.value = nullptr;
}
DefaultConditionFilter::~DefaultConditionFilter()
{}

RC DefaultConditionFilter::init(const ConDesc &left, const ConDesc &right, AttrType attr_type, CompOp comp_op)
{
  if (attr_type < CHARS || attr_type > DATES) {
    LOG_ERROR("Invalid condition with unsupported attribute type: %d", attr_type);
    return RC::INVALID_ARGUMENT;
  }

  if (comp_op < EQUAL_TO || comp_op >= NO_OP) {
    LOG_ERROR("Invalid condition with unsupported compare operation: %d", comp_op);
    return RC::INVALID_ARGUMENT;
  }

  left_ = left;
  right_ = right;
  attr_type_ = attr_type;
  comp_op_ = comp_op;
  return RC::SUCCESS;
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

bool isValidDate_fileter(char *date) {
    const std::vector<std::string> &dates = split_(date, '-');
    if (dates.size() != 3) {
        LOG_ERROR("Failed to parser date filed");
        return false;
    }
    int year_len = 4, month_len = 2, day_len = 2;
    // 1. judge year
    if (dates[0].size() < year_len) {
        std::string str = dates[0];
        int diff = year_len - dates[0].size();
        for (int i = 0; i < diff; i++) {
            str = "0" + str;
        }
        memmove(date + diff, date, strlen(date) + diff);
        for (int i = 0; i < diff; i++) {
            date[i] = str[i];
        }
    }
    if (dates[1].size() < month_len) {
        std::string str = dates[1];
        int diff = month_len - dates[1].size();
        for (int i = 0; i < diff; i++) {
            str = "0" + str;
        }
        memmove(date + diff + year_len + 1, date + year_len + 1, strlen(date) + diff);
        for (int i = 0; i < month_len; i++) {
            date[year_len + 1 + i] = str[i];
        }
    }
    if (dates[2].size() < day_len) {
        std::string str = dates[2];
        int diff = 2 - dates[2].size();
        for (int i = 0; i < diff; i++) {
            str = "0" + str;
        }
        memmove(date + diff + 8, date + 8, strlen(date) + diff);
        for (int i = 0; i < 2; i++) {
            date[8 + i] = str[i];
        }
    }
    int year = atoi(dates[0].c_str());
    bool isLeap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    if (year > 2038) {
        LOG_ERROR("year is should not bigger than 2038!");
        return false;
    }
    int month = atoi(dates[1].c_str());
    int day = atoi(dates[2].c_str());
    if (year == 2038 && month > 2) {
        LOG_ERROR("if year == 2038, month is should not bigger than 2");
        return false;
    }
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 11 || month == 12) {
        if (day <= 0 || day > 31) {
            LOG_ERROR("%d month has %d day is should not bigger than 31 or smaller than 0", month, day);
            return false;
        }
    } else if (month == 2) {
        if (day <= 0 || day > 28 + isLeap) {
            LOG_ERROR(
                    "%d year leap state is  %d . so %d month is should not have bigger than 28 (29) or smaller than 0 days",
                    year, isLeap, month);
            return false;
        }
    } else {
        if (day <= 0 || day > 30) {
            LOG_ERROR("%d month is should not have bigger than 30 or smaller than 0 days", month);
            return false;
        }
    }
    return true;
}
RC DefaultConditionFilter::init(Table &table, const Condition &condition)
{
  const TableMeta &table_meta = table.table_meta();
  ConDesc left;
  ConDesc right;

  AttrType type_left = UNDEFINED;
  AttrType type_right = UNDEFINED;

  if (1 == condition.left_is_attr) {
    left.is_attr = true;
    const FieldMeta *field_left = table_meta.field(condition.left_attr.attribute_name);
    if (nullptr == field_left) {
      LOG_WARN("No such field in condition. %s.%s", table.name(), condition.left_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    left.attr_length = field_left->len();
    left.attr_offset = field_left->offset();

    left.value = nullptr;

    type_left = field_left->type();
  } else {
    left.is_attr = false;
    left.value = condition.left_value.data;  // 校验type 或者转换类型
    type_left = condition.left_value.type;

    left.attr_length = 0;
    left.attr_offset = 0;
  }

  if (1 == condition.right_is_attr) {
    right.is_attr = true;
    const FieldMeta *field_right = table_meta.field(condition.right_attr.attribute_name);
    if (nullptr == field_right) {
      LOG_WARN("No such field in condition. %s.%s", table.name(), condition.right_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    right.attr_length = field_right->len();
    right.attr_offset = field_right->offset();
    type_right = field_right->type();

    right.value = nullptr;
  } else {
    right.is_attr = false;
    right.value = condition.right_value.data;
    type_right = condition.right_value.type;

    right.attr_length = 0;
    right.attr_offset = 0;
  }
  if (type_left == DATES && !left.is_attr) {
      if (!isValidDate_fileter(static_cast<char *>(left.value))) {
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
  }
    if (type_right == DATES && !right.is_attr) {
        if (!isValidDate_fileter(static_cast<char *>(right.value))) {
            return  RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
    }
  // 校验和转换
  //  if (!field_type_compare_compatible_table[type_left][type_right]) {
  //    // 不能比较的两个字段， 要把信息传给客户端
  //    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  //  }
  // NOTE：这里没有实现不同类型的数据比较，比如整数跟浮点数之间的对比
  // 但是选手们还是要实现。这个功能在预选赛中会出现
  if (type_left != type_right) {
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

  return init(left, right, type_left, condition.comp);
}

bool DefaultConditionFilter::filter(const Record &rec) const
{
  char *left_value = nullptr;
  char *right_value = nullptr;

  if (left_.is_attr) {  // value
    left_value = (char *)(rec.data + left_.attr_offset);
  } else {
    left_value = (char *)left_.value;
  }

  if (right_.is_attr) {
    right_value = (char *)(rec.data + right_.attr_offset);
  } else {
    right_value = (char *)right_.value;
  }

  int cmp_result = 0;
  switch (attr_type_) {
    case CHARS: {  // 字符串都是定长的，直接比较
      // 按照C字符串风格来定
      cmp_result = strcmp(left_value, right_value);
    } break;
    case INTS: {
      // 没有考虑大小端问题
      // 对int和float，要考虑字节对齐问题,有些平台下直接转换可能会跪
      int left = *(int *)left_value;
      int right = *(int *)right_value;
      cmp_result = left - right;
    } break;
    case FLOATS: {
      float left = *(float *)left_value;
      float right = *(float *)right_value;
      cmp_result = (int)(left - right);
    } break;
    case DATES: {
          std::vector<std::string> left = split_((char *) left_value, '-');
          std::vector<std::string> right = split_((char *) right_value, '-');
          int l_year = atoi(left[0].c_str()), r_year = atoi(right[0].c_str());
          if (l_year != r_year) {
              cmp_result = l_year - r_year;
              break;
          }
          int l_month = atoi(left[1].c_str()), r_month = atoi(right[1].c_str());
          if (l_month != r_month) {
              cmp_result = l_month - r_month;
          } else {
              int l_day = atoi(left[2].c_str()), r_day = atoi(right[2].c_str());
              cmp_result = l_day - r_day;
          }
      }
          break;
    default: {
    }
  }

  switch (comp_op_) {
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

    default:
      break;
  }

  LOG_PANIC("Never should print this.");
  return cmp_result;  // should not go here
}

CompositeConditionFilter::~CompositeConditionFilter()
{
  if (memory_owner_) {
    delete[] filters_;
    filters_ = nullptr;
  }
}

RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num, bool own_memory)
{
  filters_ = filters;
  filter_num_ = filter_num;
  memory_owner_ = own_memory;
  return RC::SUCCESS;
}
RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num)
{
  return init(filters, filter_num, false);
}

RC CompositeConditionFilter::init(Table &table, const Condition *conditions, int condition_num)
{
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
  return init((const ConditionFilter **)condition_filters, condition_num, true);
}

bool CompositeConditionFilter::filter(const Record &rec) const
{
  for (int i = 0; i < filter_num_; i++) {
    if (!filters_[i]->filter(rec)) {
      return false;
    }
  }
  return true;
}
