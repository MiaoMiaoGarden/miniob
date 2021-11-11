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

#ifndef __OBSERVER_SQL_EXECUTOR_VALUE_H_
#define __OBSERVER_SQL_EXECUTOR_VALUE_H_

#include <string.h>
#include<sstream>
#include<fstream>
#include <string>
#include <ostream>
#include <utility>

class TupleValue {
public:

  TupleValue() = default;
  virtual ~TupleValue() = default;
  virtual bool is_null() const = 0;
  virtual void to_string(std::ostream &os) const = 0;
  virtual int compare(const TupleValue &other) const = 0;
  virtual std::string get_string_value() const = 0;
private:
};

class IntValue : public TupleValue {
public:
    explicit IntValue(int value) : value_(value) {
    }

    bool is_null() const override {
        char *char_value = (char *) (&value_);
        if (*char_value == '!') {
            return true;
        } else {
            return false;
        }
    }

    void to_string(std::ostream &os) const override {
        if (is_null()) {
            os << "null";
        } else {
            os << value_;
        }
    }

    int compare(const TupleValue &other) const override {
        const IntValue &int_other = (const IntValue &) other;
        int result = value_ - int_other.value_;
        if (result > 0) {
            return 1;
        }
        if (result < 0) {
            return -1;
        }
        return 0;
    }

  int get_value(){
    return value_;
  }
  
  std::string get_string_value() const override {
    return std::to_string(value_);
  }

private:
    int value_;
};

class FloatValue : public TupleValue {
public:
  explicit FloatValue(float value) : value_(value) {
  }

  bool is_null() const override {
    char *char_value = (char*)(&value_);
    if(*char_value=='!'){
      return true;
    } else {
      return false;
    }
  }
  void to_string(std::ostream &os) const override {
    if(is_null()){
      os << "null";
    } else {
      os << value_;
    }
  }

  int compare(const TupleValue &other) const override {
    const FloatValue & float_other = (const FloatValue &)other;
    float result = value_ - float_other.value_;
    if (result > 0) { // 浮点数没有考虑精度问题
      return 1;
    }
    if (result < 0) {
      return -1;
    }
    return 0;
  }

  float get_value(){
    return value_;
  }

  std::string get_string_value() const override {
    return std::to_string(value_);
  }
private:
    float value_;
};

class StringValue : public TupleValue {
public:
  StringValue(const char *value, int len) : value_(value, len){
  }
  explicit StringValue(const char *value) : value_(value) {
  }
  bool is_null() const override {
    return value_[0] == '!';
  }

  void to_string(std::ostream &os) const override {
    if(is_null()){
      os << "null";
    } else {
      os << value_;
    }
  }

  int compare(const TupleValue &other) const override {
    const StringValue &string_other = (const StringValue &)other;
    int result = strcmp(value_.c_str(), string_other.value_.c_str());
    if (result < 0) {
        return -1;
    }
    if (result > 0) {
        return 1;
    }
    return 0;
  }

  std::string get_value(){
    return value_;
  }

  std::string get_string_value() const override {
    return value_;
  }

private:
  std::string value_;
};

class DateValue : public TupleValue {
public:
    explicit DateValue(int value) : value_(value) {
    }

    bool is_null() const override {
        char *char_value = (char *) (&value_);
        if (*char_value == '!') {
            return true;
        } else {
            return false;
        }
    }

    void to_string(std::ostream &os) const override {
        if (is_null()) {
            os << "null";
        } else {
            // os << value_;
            int year = value_ / 10000;
            int month = (value_ - year * 10000) / 100;
            int day = value_ - year * 10000 - month * 100;
            std::string year_str = std::to_string(year);
            std::string month_str = std::to_string(month);
            std::string day_str = std::to_string(day);
            if (month_str.size() < 2)
                month_str = "0" + month_str;
            if (day_str.size() < 2)
                day_str = "0" + day_str;
            std::string date = year_str + "-" + month_str + "-" + day_str;
            os << date;
        }
    }

    int compare(const TupleValue &other) const override {
        const DateValue &date_other = (const DateValue &) other;
        return value_ - date_other.value_;
    }

    int get_value() {
        return value_;
    }

    std::string get_string_value() const override {
      return std::to_string(value_);
    }

private:
    int value_;
};

class TEXTValue : public TupleValue {
public:
    explicit TEXTValue(std::string &value) : value_(value) {
    }

    bool is_null() const override {
        return value_[0] == '!';
    }

    void to_string(std::ostream &os) const override {
        if (is_null()) {
            os << "null";
        } else {
            std::ifstream infile(value_.c_str());
            printf("The file path is %s\n", value_.c_str());
            std::string temp;
            while (getline(infile, temp)) {
                os << temp;
            }
        }
    }

    int compare(const TupleValue &other) const override {
        const StringValue &string_other = (const StringValue &) other;
        int result = strcmp(value_.c_str(), string_other.get_string_value().c_str());
        if (result < 0) {
            return -1;
        }
        if (result > 0) {
            return 1;
        }
        return 0;
    }

    std::string get_value() {
        return value_;
    }
    std::string get_string_value() const override {
        return value_;
    }

private:
    std::string value_;
};

#endif //__OBSERVER_SQL_EXECUTOR_VALUE_H_
