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

bool is_valid_aggre(const char *attr) {  // number, float, *
    if (strcmp("*", attr) == 0) {
        return true;
    }

    int i = 0;
    int length = strlen(attr);
    if (i >= length) return false;

    if (!('0' <= attr[i] && attr[i] <= '9') && attr[i] != '-' && attr[i] != '+') {
        return false;
    }

    for (; i < length; i++) {
        if (('0' <= attr[i] && attr[i] <= '9') || attr[i] == '.') {
            continue;
        } 
        return false;
    }
    return true;
}


RC AggregateMinValue::add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type, bool count_null) {
    RC rc = RC::SUCCESS;
    if (tuple_value->is_null()) {
        return rc;
    }
    if (value_.get() == nullptr || value_->compare(*tuple_value) > 0) {
        value_ = tuple_value;
    }
    return rc;
}

RC AggregateMaxValue::add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type, bool count_null) {
    RC rc = RC::SUCCESS;
    if (tuple_value->is_null()) {
        return rc;
    }
    if (value_.get() == nullptr || value_->compare(*tuple_value) < 0) {
        value_ = tuple_value;
    }
    return rc;
}

RC AggregateAvgValue::add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type, bool count_null) {
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
        all_null_ = false;
    } else {
        IntValue *int_value = dynamic_cast<IntValue *>(tuple_value.get());
        sum += int_value->get_value();
        all_null_ = false;
    }
    count += 1;
    return rc;
}

RC AggregateCountValue::add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type, bool count_null) {
    if ( (tuple_value->is_null() && count_null) || (!tuple_value->is_null()) ) {
        count += 1;
    }
    return RC::SUCCESS;
}

RC AggregateNonValue::add(const std::shared_ptr<TupleValue> &tuple_value, AttrType type, bool count_null) {
    tuple_value_ = tuple_value;
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
    if(all_null_){
        return nullptr;
    }
    float avg = round(100*(float)sum/count)/100.0;
    std::shared_ptr<TupleValue> value = std::make_shared<FloatValue>(avg);
    return value;
}

std::shared_ptr<TupleValue> AggregateCountValue::value() {
    std::shared_ptr<TupleValue> value = std::make_shared<FloatValue>(count);
    return value;
}

std::shared_ptr<TupleValue> AggregateNonValue::value() {
    // std::shared_ptr<TupleValue> value(&tuple_value_);
    // return value;
    return tuple_value_;
}
