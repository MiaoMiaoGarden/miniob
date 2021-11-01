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
#include "sql/executor/aggregate.h"
#include "storage/common/table.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"

bool is_valid_aggre(const char *attr, AggreType aggre_type) {  // number, float, *
    if (strcmp("*", attr) == 0) {
        return aggre_type == COUNT;
    }

    int i = 0;
    int length = strlen(attr);
    if (i >= length) return false;

    if (!('0' <= attr[i] && attr[i] <= '9') && attr[i] != '-' && attr[i] != '+') {
        return false;
    }

    for (; i < length; i++) {
        if (('0' <= attr[i] && attr[i] <= '9') || attr[i] == '.') {
            if (i == length - 1) {
                return true;
            }
            continue;
        } else {
            return false;
        }
    }
}

void parse_attr(char *attribute_name, AggreType aggre_type, char *attr_name) {
    if (aggre_type == NON) return;
    int j = 0;
    for (int i = 0; i < strlen(attribute_name); i++) {
        if (i == 0) {
            if (aggre_type == COUNT) {
                i += 5;
            } else {
                i += 3;
            }
        }
        if (attribute_name[i] == '(' || attribute_name[i] == ')' || attribute_name[i] == ' ') {
            continue;
        }
        attr_name[j++] = attribute_name[i];
    }
    attr_name[j] = '\0';
}

RC AggregateMinValue::add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type) {
    RC rc = RC::SUCCESS;
    if (tuple_value->is_null()) {
        return rc;
    }
    if (value_.get() == nullptr || value_->compare(*tuple_value) > 0) {
        value_ = tuple_value;
    }
    return rc;
}

RC AggregateMaxValue::add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type) {
    RC rc = RC::SUCCESS;
    if (tuple_value->is_null()) {
        return rc;
    }
    if (value_.get() == nullptr || value_->compare(*tuple_value) < 0) {
        value_ = tuple_value;
    }
    return rc;
}

RC AggregateAvgValue::add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type) {
    RC rc = RC::SUCCESS;
    if (type != FLOATS && type != INTS) {
        rc = RC::GENERIC_ERROR;
        return rc;
    }
    if (tuple_value->is_null()) {
        return rc;
    }
    if (type == FLOATS) {
        FloatValue *float_value = dynamic_cast<FloatValue *>(tuple_value.get());
        sum += float_value->get_value();
    } else {
        IntValue *int_value = dynamic_cast<IntValue *>(tuple_value.get());
        sum += int_value->get_value();
    }
    count += 1;
    return rc;
}

RC AggregateCountValue::add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type) {
    if (!tuple_value->is_null()) {
        count += 1;
    }
    return RC::SUCCESS;
}

std::shared_ptr<TupleValue> AggregateMinValue::value() {
    // 需要在处理精度问题
    return value_;
}

std::shared_ptr<TupleValue> AggregateMaxValue::value() {
    // 需要在处理精度问题
    return value_;
}

std::shared_ptr<TupleValue> AggregateAvgValue::value() {
    float avg = round(100*(float)sum/count)/100.0;
    std::shared_ptr<TupleValue> value = std::make_shared<FloatValue>(avg);
    return value;
}

std::shared_ptr<TupleValue> AggregateCountValue::value() {
    std::shared_ptr<TupleValue> value = std::make_shared<FloatValue>(count);
    return value;
}
