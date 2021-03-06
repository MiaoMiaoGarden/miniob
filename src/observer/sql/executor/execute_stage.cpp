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
// Created by Longda on 2021/4/13.
//

#include <memory>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <unordered_map>

#include "execute_stage.h"

#include "sql/executor/aggregate.h"
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

using namespace common;

RC create_selection_executor(Trx *trx, const Selects &selects, Table *table, 
                    const char *table_name, SelectExeNode &select_node);

static RC schema_add_field(Table *table, const char *field_name, TupleSchema &schema);

RC cross_join(std::vector<TupleSet> &tuple_sets, const Selects &selects, 
                    const std::vector<SelectExeNode*> &select_nodes,
                    TupleSet &tuple_set);

RC do_cross_join(std::vector<TupleSet> &tuple_sets, int index,
                    std::vector<const Condition *> conditions,
                    TupleSet &tuple_set, 
                    std::unordered_map<std::string, const Tuple*> &tuples_map,
                    std::unordered_map<std::string, const TupleSchema*> &schemas_map);

//! Constructor
//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag) {}

//! Destructor
ExecuteStage::~ExecuteStage() {}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag) {
    ExecuteStage *stage = new(std::nothrow) ExecuteStage(tag.c_str());
    if (stage == nullptr) {
        LOG_ERROR("new ExecuteStage failed");
        return nullptr;
    }
    stage->set_properties();
    return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties() {
    //  std::string stageNameStr(stageName);
    //  std::map<std::string, std::string> section = theGlobalProperties()->get(
    //    stageNameStr);
    //
    //  std::map<std::string, std::string>::iterator it;
    //
    //  std::string key;

    return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize() {
    LOG_TRACE("Enter");

    std::list<Stage *>::iterator stgp = next_stage_list_.begin();
    default_storage_stage_ = *(stgp++);
    mem_storage_stage_ = *(stgp++);

    LOG_TRACE("Exit");
    return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup() {
    LOG_TRACE("Enter");

    LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event) {
    LOG_TRACE("Enter\n");

    handle_request(event);

    LOG_TRACE("Exit\n");
    return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context) {
    LOG_TRACE("Enter\n");

    // here finish read all data from disk or network, but do nothing here.
    ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
    SQLStageEvent *sql_event = exe_event->sql_event();
    sql_event->done_immediate();

    LOG_TRACE("Exit\n");
    return;
}

void ExecuteStage::handle_request(common::StageEvent *event) {
    ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
    SessionEvent *session_event = exe_event->sql_event()->session_event();
    Query *sql = exe_event->sqls();
    const char *current_db = session_event->get_client()->session->get_current_db().c_str();

    CompletionCallback *cb = new(std::nothrow) CompletionCallback(this, nullptr);
    if (cb == nullptr) {
        LOG_ERROR("Failed to new callback for ExecutionPlanEvent");
        exe_event->done_immediate();
        return;
    }
    exe_event->push_callback(cb);

    switch (sql->flag) {
        case SCF_SELECT: { // select
            do_select(current_db, sql, exe_event->sql_event()->session_event());
            exe_event->done_immediate();
        }
        break;

        case SCF_INSERT:
        case SCF_UPDATE:
        case SCF_DELETE:
        case SCF_CREATE_TABLE:
        case SCF_SHOW_TABLES:
        case SCF_DESC_TABLE:
        case SCF_DROP_TABLE:
        case SCF_CREATE_INDEX:
        case SCF_DROP_INDEX:
        case SCF_LOAD_DATA: {
            StorageEvent *storage_event = new(std::nothrow) StorageEvent(exe_event);
            if (storage_event == nullptr) {
                LOG_ERROR("Failed to new StorageEvent");
                event->done_immediate();
                return;
            }

            default_storage_stage_->handle_event(storage_event);
        }
            break;
        case SCF_SYNC: {
            RC rc = DefaultHandler::get_default().sync();
            session_event->set_response(strrc(rc));
            exe_event->done_immediate();
        }
            break;
        case SCF_BEGIN: {
            session_event->get_client()->session->set_trx_multi_operation_mode(true);
            session_event->set_response(strrc(RC::SUCCESS));
            exe_event->done_immediate();
        }
            break;
        case SCF_COMMIT: {
            Trx *trx = session_event->get_client()->session->current_trx();
            RC rc = trx->commit();
            session_event->get_client()->session->set_trx_multi_operation_mode(false);
            session_event->set_response(strrc(rc));
            exe_event->done_immediate();
        }
            break;
        case SCF_ROLLBACK: {
            Trx *trx = session_event->get_client()->session->current_trx();
            RC rc = trx->rollback();
            session_event->get_client()->session->set_trx_multi_operation_mode(false);
            session_event->set_response(strrc(rc));
            exe_event->done_immediate();
        }
            break;
        case SCF_HELP: {
            const char *response = "show tables;\n"
                                   "desc `table name`;\n"
                                   "create table `table name` (`column name` `column type`, ...);\n"
                                   "create index `index name` on `table` (`column`);\n"
                                   "insert into `table` values(`value1`,`value2`);\n"
                                   "update `table` set column=value [where `column`=`value`];\n"
                                   "delete from `table` [where `column`=`value`];\n"
                                   "select [ * | `columns` ] from `table`;\n";
            session_event->set_response(response);
            exe_event->done_immediate();
        }
            break;
        case SCF_EXIT: {
            // do nothing
            const char *response = "Unsupported\n";
            session_event->set_response(response);
            exe_event->done_immediate();
        }
            break;
        default: {
            exe_event->done_immediate();
            LOG_ERROR("Unsupported command=%d\n", sql->flag);
        }
    }
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right) {
    if (!session->is_trx_multi_operation_mode()) {
        if (all_right) {
            trx->commit();
        } else {
            trx->rollback();
        }
    }
}


bool isLeapYear_(int year){
    if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))
    {
        return true;
    }
    return false;
}
bool is_date(int year, int mon, int day) {
    int Maxdays[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (mon < 1 || mon > 12) // ?????????
    {
        return false;
    }
    if (year < 1970) // ?????????????????????????????????????????????????????????0????????????
    {
        return false;
    }
    if (mon == 2 && day == 29 && isLeapYear_(year))  //??????2???29???
    {
        return true;
    }
    if (day<1 || day>Maxdays[mon])// ?????????
    {
        return false;
    }
    return true; //????????????????????????
}


bool is_valid_date(int date) {
    int year = date / 10000;
    int month = (date - year * 10000) / 100;
    int day = date - year * 10000 - month * 100;
    return is_date(year, month, day);
}
// ?????????????????????????????????????????????????????????????????????????????????where?????????????????????????????????????????????????????????
// ???????????????????????????. ???????????????????????????resolve????????????execution????????????????????????
RC ExecuteStage::do_select(const char *db, Query *sql, SessionEvent *session_event) {
    std::stringstream ss;
    RC rc = RC::SUCCESS;
    Session *session = session_event->get_client()->session;
    Trx *trx = session->current_trx();
    const Selects &selects = sql->sstr.selection;

    char response[256];
    //??? tables_map ?????? ExecuteStage ????????????????????????????????????????????????
    std::unordered_map<std::string, Table*> tables_map;
    int relation_num = selects.relation_num;
    for (int i = 0; i < relation_num; i++) {
        const char *table_name = selects.relations[i];
        Table *table = DefaultHandler::get_default().find_table(db, table_name);
        if (table == nullptr) {
            LOG_WARN("No such table [%s] in db [%s]", table_name, db);
            snprintf(response, sizeof(response), "FAILURE\n");
            session_event->set_response(response);
            return RC::SCHEMA_TABLE_NOT_EXIST;
        }
        std::string table_name1(table_name);
        tables_map[table_name1] = table;
    }

    // ??????????????????????????????????????????condition????????????????????????????????? select ????????????
    for(int i = 0; i < selects.condition_num; i++) {
        if(!selects.conditions[i].left_is_attr &&
           selects.conditions[i].left_value.type == DATES &&
           !is_valid_date(*((int *)selects.conditions[i].left_value.data))) {
            rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
            break;
        }
        if(!selects.conditions[i].right_is_attr &&
           selects.conditions[i].right_value.type == DATES &&
           !is_valid_date(*((int *)selects.conditions[i].right_value.data))) {
            rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
            break;
        }
    }
    if(rc != RC::SUCCESS) {
        ss<<(rc == RC::SUCCESS ? " " : "FAILURE")<<"\n";
        session_event->set_response(ss.str());
        return rc;
    }
    // ??????????????????????????????????????????condition?????????????????????????????????select ????????????
    std::vector<SelectExeNode *> select_nodes;
  
    for (size_t i = 0; i < selects.relation_num; i++) {
        std::string table_name(selects.relations[i]);
        SelectExeNode *select_node = new SelectExeNode;
        rc = create_selection_executor(trx, selects, tables_map[table_name], selects.relations[i], *select_node);
        if (rc != RC::SUCCESS) {
            snprintf(response, sizeof(response), "FAILURE\n");
            session_event->set_response(response);
            delete select_node;
            for (SelectExeNode *&tmp_node: select_nodes) {
                delete tmp_node;
            }
            end_trx_if_need(session, trx, false);
            return rc;
        }
        select_nodes.push_back(select_node);
    }

    if (select_nodes.empty()) {
        LOG_ERROR("No table given");
        end_trx_if_need(session, trx, false);
        return RC::SQL_SYNTAX;
    }

    std::vector<TupleSet> tuple_sets;
    for (SelectExeNode *&node: select_nodes) {
        TupleSet tuple_set;
        rc = node->execute(tuple_set);
        if (rc != RC::SUCCESS) {
            for (SelectExeNode *&tmp_node: select_nodes) {
                delete tmp_node;
            }
            end_trx_if_need(session, trx, false);
            return rc;
        } else {
            tuple_sets.push_back(std::move(tuple_set));
        }
    }

    TupleSchema output_scheam;
    rc = gen_output_scheam(tables_map, selects, output_scheam);
    output_scheam.set_groupby(selects.groupby_attr,selects.relations[0]);
    if (rc != RC::SUCCESS) {
        snprintf(response, sizeof(response), "FAILURE\n");
        session_event->set_response(response);
        for (SelectExeNode *&tmp_node: select_nodes) {
            delete tmp_node;
        }
        end_trx_if_need(session, trx, false);
        return rc;
    }
    // ?????????????????????tuple_set????????????tuple_set, ????????????????????????????????????tuple_set

    TupleSet tuple_set;
    if (select_nodes.size() > 1) {
        // ????????????????????????????????????join??????
        RC rc = cross_join(tuple_sets, selects, select_nodes, tuple_set);
        if (rc != RC::SUCCESS) {
            snprintf(response, sizeof(response), "FAILURE\n");
            session_event->set_response(response);
            for (SelectExeNode *&select_node: select_nodes) {
                delete select_node;
            }
            end_trx_if_need(session, trx, false);
            return rc;
        }
    } else {
        // ???????????????????????????????????????????????????
        tuple_set = std::move(tuple_sets.front());
    }

    TupleSet tuple_set1; //???????????????tuple_set
    tuple_set1.set_schema(output_scheam);
    rc = tuple_set1.set_tuple_set(std::move(tuple_set));
    if (rc != RC::SUCCESS) {
        snprintf(response, sizeof(response), "FAILURE\n");
        session_event->set_response(response);
        for (SelectExeNode *&tmp_node: select_nodes) {
            delete tmp_node;
        }
        end_trx_if_need(session, trx, false);
        return rc;
    }
    std::stringstream ss;
    tuple_set1.print(ss, select_nodes.size() != 1);
    for (SelectExeNode *&tmp_node: select_nodes) {
        delete tmp_node;
    }
    session_event->set_response(ss.str());
    end_trx_if_need(session, trx, true);
    return rc;
}

RC ExecuteStage::gen_output_scheam(std::unordered_map<std::string, Table*> &tables_map, 
                const Selects &selects, TupleSchema &output_scheam){

    for (int i = selects.attr_num - 1; i >= 0; i--) {
        const RelAttr &attr = selects.attributes[i];
        if (attr.aggre_type != AggreType::NON) {
            // ????????????
            // char attr_name[100];
            // parse_attr(attr.attribute_name, attr.aggre_type, attr_name);
            const char *table_name = attr.relation_name != nullptr ? attr.relation_name : selects.relations[0];
            std::string table_name1(table_name);
            AttrType attr_type;

            Table *table = tables_map[table_name1];
            if (attr.aggre_type != AggreType::NON && is_valid_aggre(attr.attribute_name, attr.aggre_type)) {  // count(1) find the first one attr
                // count(*), count(1), ...
                // ?????????????????????
                attr_type = table->table_meta().field(0)->type();
            } else {
                attr_type = table->table_meta().field(attr.attribute_name)->type();
            }
            output_scheam.add(attr_type, selects.relations[0], attr.attribute_name, true, attr.aggre_type);
        } else {
            // ?????????
            if (attr.relation_name == nullptr) {
                // select * from t, t1;
                if (strcmp("*", attr.attribute_name) == 0) {
                    for (int i = selects.relation_num - 1; i >= 0; i--) {
                        std::string table_name(selects.relations[i]);
                        Table* table = tables_map[table_name];
                        TupleSchema schema;
                        TupleSchema::from_table(table, schema);
                        output_scheam.append(schema);
                    }
                    break;
                } else if (selects.relation_num == 1) {
                    std::string table_name(selects.relations[0]);
                    Table* table = tables_map[table_name];
                    RC rc = schema_add_field(table, attr.attribute_name, output_scheam);
                    if (rc != RC::SUCCESS) {
                        return rc;
                    }
                } else {
                    return RC::SCHEMA_TABLE_NOT_EXIST;
                }
            } else { 
                std::string table_name(attr.relation_name);
                Table* table = tables_map[table_name];
                if (strcmp("*", attr.attribute_name) == 0) {
                    TupleSchema schema;
                    TupleSchema::from_table(table, schema);
                    output_scheam.append(schema);
                } else {
                    RC rc = schema_add_field(table, attr.attribute_name, output_scheam);
                    if (rc != RC::SUCCESS) {
                        return rc;
                    }
                }
            }
        }
    }
    return RC::SUCCESS;
}

bool match_table(const Selects &selects, const char *table_name_in_condition, const char *table_name_to_match) {
    if (table_name_in_condition != nullptr) {
        return 0 == strcmp(table_name_in_condition, table_name_to_match);
    }

    return selects.relation_num == 1;
}

static RC schema_add_field(Table *table, const char *field_name, TupleSchema &schema) {
    const FieldMeta *field_meta = table->table_meta().field(field_name);
    if (nullptr == field_meta) {
        LOG_WARN("No such field. %s.%s", table->name(), field_name);
        return RC::SCHEMA_FIELD_MISSING;
    }

    schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name());
    return RC::SUCCESS;
}

// ??????????????????????????????????????????condition?????????????????????????????????select ????????????
RC create_selection_executor(Trx *trx, const Selects &selects, Table *table,
                const char *table_name, SelectExeNode &select_node) {
    // ???????????????????????????Attr
    TupleSchema schema;
    if (selects.relation_num > 1) {
        // select t1.age from t1, t2 where t1.id = t2.id;
        // ???????????????????????????????????????????????????????????????????????????????????????(t1.age, t1.id, t2.id)????????????, 
        // ???????????????????????????????????????????????????????????????????????????????????????????????????????????????
        TupleSchema::from_table(table, schema);
    } else {
        for (int i = selects.attr_num - 1; i >= 0; i--) {
            const RelAttr &attr = selects.attributes[i];
            if (nullptr == attr.relation_name || 0 == strcmp(table_name, attr.relation_name)) {
                /*
                char parsed[100];
                parse_attr(attr.attribute_name, attr.aggre_type, parsed); // if not aggre, will do nothing and return
                */
                if (0 == strcmp("*", attr.attribute_name) || 
                        (attr.aggre_type != NON && is_valid_aggre(attr.attribute_name, attr.aggre_type))) {
                    // ???????????????????????????
                    TupleSchema::from_table(table, schema);
                    break; // ?????????????????????* ??????????????????????????????
                } else {
                    // ???????????????????????????
                    RC rc = RC::SUCCESS;
                    if (attr.aggre_type != NON) {
                        rc = schema_add_field(table, attr.attribute_name, schema);
                    }
                    if (rc != RC::SUCCESS) {
                        return rc;
                    }
                }
            }
        }
        RC rc = RC::SUCCESS;
        if(selects.groupby_attr!=nullptr){
            rc = schema_add_field(table, selects.groupby_attr->attribute_name, schema);
        }
        if (rc != RC::SUCCESS) {
            return rc;
        }
    }

    // ???????????????????????????????????????, ??????????????????????????????
    std::vector<DefaultConditionFilter *> condition_filters;
    for (size_t i = 0; i < selects.condition_num; i++) {
        const Condition &condition = selects.conditions[i];
        if ((condition.left_is_attr == 0 && condition.right_is_attr == 0) || // ???????????????
            (condition.left_is_attr == 1 && condition.right_is_attr == 0 &&
             match_table(selects, condition.left_attr.relation_name, table_name)) ||  // ???????????????????????????
            (condition.left_is_attr == 0 && condition.right_is_attr == 1 &&
             match_table(selects, condition.right_attr.relation_name, table_name)) ||  // ?????????????????????????????????
            (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
             match_table(selects, condition.left_attr.relation_name, table_name) &&
             match_table(selects, condition.right_attr.relation_name, table_name)) // ?????????????????????????????????????????????
                ) {
            DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
            RC rc = condition_filter->init(*table, condition);
            if (rc != RC::SUCCESS) {
                delete condition_filter;
                for (DefaultConditionFilter *&filter: condition_filters) {
                    delete filter;
                }
                return rc;
            }
            condition_filters.push_back(condition_filter);
        }
    }

    return select_node.init(trx, table, std::move(schema), std::move(condition_filters));
}

RC cross_join(std::vector<TupleSet> &tuple_sets, const Selects &selects, 
                    const std::vector<SelectExeNode*> &select_nodes,
                    TupleSet &tuple_set) {
    TupleSchema scheam;
    std::unordered_map<std::string, const TupleSchema*> schemas_map;

    for (auto& tuple_set1 : tuple_sets) {
        std::string table_name(tuple_set1.get_schema().fields()[0].table_name());
        schemas_map[table_name] = &tuple_set1.get_schema();
        scheam.append(tuple_set1.get_schema());
    }

    std::vector<const Condition *> conditions;
    for (size_t i = 0; i < selects.condition_num; i++) {
        const Condition &condition = selects.conditions[i];
        if (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
            0 != strcmp(condition.left_attr.relation_name, condition.right_attr.relation_name)) {
            conditions.push_back(&condition);
        }
    }
    tuple_set.set_schema(scheam);
    std::unordered_map<std::string, const Tuple*> tuples_map;
    return do_cross_join(tuple_sets, tuple_sets.size() - 1, conditions, tuple_set, tuples_map, schemas_map);
}

RC do_cross_join(std::vector<TupleSet> &tuple_sets, int index, 
                    std::vector<const Condition *> conditions,
                    TupleSet &tuple_set, 
                    std::unordered_map<std::string, const Tuple*> &tuples_map,
                    std::unordered_map<std::string, const TupleSchema*> &schemas_map) {

    if (index == -1) {
        for (auto &condition: conditions) {
            std::string left_table(condition->left_attr.relation_name);
            char *left_attr = condition->left_attr.attribute_name;
            std::string right_table(condition->right_attr.relation_name);
            char *right_attr = condition->right_attr.attribute_name;
            
            int i = schemas_map[left_table]->index_of_field(left_table.c_str(), left_attr);
            int j = schemas_map[right_table]->index_of_field(right_table.c_str(), right_attr);
            if ( i == -1 || j == -1) {
                return RC::SCHEMA_FIELD_NAME_ILLEGAL;
            }

            const TupleValue &tuple_value1 = tuples_map[left_table]->get(i);
            const TupleValue &tuple_value2 = tuples_map[right_table]->get(j);
            int result = tuple_value1.compare(tuple_value2);
            if ((result == 0 && (condition->comp == CompOp::EQUAL_TO || condition->comp == CompOp::GREAT_EQUAL ||
                                 condition->comp == CompOp::LESS_EQUAL)) ||
                (result == 1 && (condition->comp == CompOp::GREAT_THAN || condition->comp == CompOp::GREAT_EQUAL)) ||
                (result == -1 && (condition->comp == CompOp::LESS_THAN || condition->comp == CompOp::LESS_EQUAL))) {
                continue;
            }
            return RC::SUCCESS;
        }
        Tuple new_tuple;
        const std::vector<TupleField> &tuple_fields = tuple_set.get_schema().fields();
        for (auto& tuple_field : tuple_fields) {
            std::string table_name(tuple_field.table_name());
            int i = schemas_map[table_name]->index_of_field(table_name.c_str(), tuple_field.field_name());
            std::shared_ptr<TupleValue> value_ptr = tuples_map[table_name]->get_pointer(i);
            new_tuple.add(value_ptr);
        }
        tuple_set.add(std::move(new_tuple));
        return RC::SUCCESS;
    }

    const TupleSet &tuple_set1 = tuple_sets[index];
    const std::vector<TupleField> &fields = tuple_set1.get_schema().fields();
    const std::vector<Tuple> &tuples = tuple_set1.tuples();
    std::string table_name(fields[0].table_name());

    int size = tuples.size();
    for (int i = 0; i < size; i++) {
        tuples_map[table_name] = &tuples[i];
        RC rc = do_cross_join(tuple_sets, index - 1, conditions, tuple_set, tuples_map, schemas_map);
        if (rc != RC::SUCCESS) {
            return rc;
        }
    }

    return RC::SUCCESS;
}

