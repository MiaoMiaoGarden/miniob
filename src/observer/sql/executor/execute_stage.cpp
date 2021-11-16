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
#include <algorithm>
#include <unordered_map>
#include <vector>

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

static RC create_selection_executor(Trx *trx, const Selects &selects, Table *table, 
                    const char *table_name, SelectExeNode &select_node);

static RC cross_join(std::vector<TupleSet> &tuple_sets, const Selects &selects, 
                    const std::vector<SelectExeNode*> &select_nodes,
                    TupleSet &tuple_set);

static RC do_cross_join(std::vector<TupleSet> &tuple_sets, int index,
                    std::vector<std::vector<const Condition *>> &conditions,
                    TupleSet &tuple_set, 
                    std::unordered_map<std::string, const Tuple*> &tuples_map,
                    std::unordered_map<std::string, const TupleSchema*> &schemas_map);

static bool do_filter(std::vector<const Condition *> &conditions, 
                    std::unordered_map<std::string, const Tuple*> &tuples_map,
                    std::unordered_map<std::string, const TupleSchema*> &schemas_map);

static void gen_conditions_group(std::list<const Condition *> &conditions,
                            std::list<const Condition *> &match_conditions,
                            std::vector<std::vector<const Condition*>> &conditions_group,
                            std::vector<TupleSet> &tuple_sets, 
                            int index);

static RC schema_add_field(Table *table, const char *field_name, TupleSchema &schema);
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
            do_select(current_db, sql, exe_event->sql_event()->session_event(), nullptr);
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

bool is_leap_year(int year) {
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

bool is_date(int year, int mon, int day) {
    int Maxdays[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (mon < 1 || mon > 12) {
        // 无效月
        return false;
    }
    if (year < 1970) {
        // 无效年（年的有效性不好界定，就认为小于0为无效）
        return false;
    }
    if (mon == 2 && day == 29 && is_leap_year(year)) {
        //闰年2月29日
        return true;
    }
    if (day<1 || day>Maxdays[mon]) {
        // 无效日
        return false;
    }
    return true; //日期有效，返回真
}

bool is_valid_date(int date) {
    int year = date / 10000;
    int month = (date - year * 10000) / 100;
    int day = date - year * 10000 - month * 100;
    return is_date(year, month, day);
}
// 这里没有对输入的某些信息做合法性校验，比如查询的列名、where条件中的列名等，没有做必要的合法性校验
// 需要补充上这一部分. 校验部分也可以放在resolve，不过跟execution放一起也没有关系
RC ExecuteStage::do_select(const char *db, Query *sql, SessionEvent *session_event, TupleSet *ret_tupleset) {
    RC rc = RC::SUCCESS;
    Session *session = session_event->get_client()->session;
    Trx *trx = session->current_trx();
    const Selects &select_raw = sql->sstr.selection;
    char response[256];

    //把 tables_map 放到 ExecuteStage 里面是不是更好一点，起到缓存作用
    std::unordered_map<std::string, Table*> tables_map;
    int relation_num = select_raw.relation_num;
    for (int i = 0; i < relation_num; i++) {
        const char *table_name = select_raw.relations[i];
        Table *table = DefaultHandler::get_default().find_table(db, table_name);
        if (table == nullptr) {
            LOG_WARN("No such table [%s] in db [%s]", table_name, db);
            snprintf(response, sizeof(response), "FAILURE\n");
            session_event->set_response(response);
            end_trx_if_need(session, trx, false);
            return RC::SCHEMA_TABLE_NOT_EXIST;
        }
        std::string table_name1(table_name);
        tables_map[table_name1] = table;
    }

    int condition_num = select_raw.condition_num;
    for(int i = 0; i < condition_num; i++) {
        if(select_raw.conditions[i].left_type == SUBSELECTION) {
            Query *subselection = (Query *) malloc(sizeof(Query));
            char *subselect_raw = select_raw.conditions[i].left_subselect;
            std::string subselect_string(subselect_raw+1);
            subselect_string[strlen(subselect_raw)-2] = ';';
            subselect_string[strlen(subselect_raw)-1] = '\0';
            RC ret = parse(subselect_string.c_str(), subselection);
            if (ret != RC::SUCCESS) {
                return ret;
            }
            TupleSet *subselection_res = new TupleSet();
            do_select(db, subselection, session_event, subselection_res);
            sql->sstr.selection.conditions[i].left_type = VALUE;
            sql->sstr.selection.conditions[i].left_value.type = subselection_res->get_schema().field(0).type();
            if(subselection_res->is_empty() || (subselection_res->size()==1 && subselection_res->get(0).get_pointer(0).get()==nullptr)){
                sql->sstr.selection.conditions[i].left_value.type = NULLS;
                sql->sstr.selection.conditions[i].left_value.data = nullptr;
                sql->sstr.selection.conditions[i].left_value.tuple_data_size = 0;
            } else if (subselection_res->size()==1) {
                sql->sstr.selection.conditions[i].left_value.tuple_data_size = 0;
                sql->sstr.selection.conditions[i].left_value.type = subselection_res->get_schema().field(0).type();
                sql->sstr.selection.conditions[i].left_value.data = const_cast<void*>(subselection_res->get(0).get(0).get_value_pointer());
            } else {
                sql->sstr.selection.conditions[i].left_value.data = nullptr;
                sql->sstr.selection.conditions[i].left_value.type = subselection_res->get_schema().field(0).type();
                for(int tuple_index = 0; tuple_index<subselection_res->size(); tuple_index++){
                    sql->sstr.selection.conditions[i].left_value.tuple_data[tuple_index] = (const_cast<void*>(subselection_res->get(tuple_index).get(0).get_value_pointer()));
                }
                sql->sstr.selection.conditions[i].left_value.tuple_data_size = subselection_res->size();
            }
        }
        if(select_raw.conditions[i].right_type == SUBSELECTION) {
            // solve_subselection(&(sql->sstr.selection.conditions[i]), 1);
            Query *subselection = (Query *) malloc(sizeof(Query));
            char *subselect_raw = select_raw.conditions[i].right_subselect;
            std::string subselect_string(subselect_raw+1);
            subselect_string[strlen(subselect_raw)-2] = ';';
            subselect_string[strlen(subselect_raw)-1] = '\0';
            RC ret = parse(subselect_string.c_str(), subselection);
            if (ret != RC::SUCCESS) {
                return ret;
            }
            TupleSet *subselection_res = new TupleSet();
            do_select(db, subselection, session_event, subselection_res);
            sql->sstr.selection.conditions[i].right_type = VALUE;
            sql->sstr.selection.conditions[i].right_value.type = subselection_res->get_schema().field(0).type();
            if(subselection_res->is_empty() || (subselection_res->size()==1 && subselection_res->get(0).get_pointer(0).get()==nullptr)){
                sql->sstr.selection.conditions[i].right_value.type = NULLS;
                sql->sstr.selection.conditions[i].right_value.data = nullptr;
                sql->sstr.selection.conditions[i].right_value.tuple_data_size = 0;
            } else if (subselection_res->size()==1) {
                sql->sstr.selection.conditions[i].right_value.tuple_data_size = 0;
                sql->sstr.selection.conditions[i].right_value.type = subselection_res->get_schema().field(0).type();
                sql->sstr.selection.conditions[i].right_value.data = const_cast<void*>(subselection_res->get(0).get(0).get_value_pointer());
            } else {
                sql->sstr.selection.conditions[i].right_value.data = nullptr;
                sql->sstr.selection.conditions[i].right_value.type = subselection_res->get_schema().field(0).type();
                for(int tuple_index = 0; tuple_index<subselection_res->size(); tuple_index++){
                    sql->sstr.selection.conditions[i].right_value.tuple_data[tuple_index] = (const_cast<void*>(subselection_res->get(tuple_index).get(0).get_value_pointer()));
                }
                sql->sstr.selection.conditions[i].right_value.tuple_data_size = subselection_res->size();
            }
        }
    }

    const Selects &selects = sql->sstr.selection;
    for(int i = 0; i < condition_num; i++) {
        if(selects.conditions[i].left_type == ATTR &&
           selects.conditions[i].left_value.type == DATES &&
           !is_valid_date(*((int *)selects.conditions[i].left_value.data))) {
            rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
            break;
        }
        if(selects.conditions[i].right_type == ATTR &&
           selects.conditions[i].right_value.type == DATES &&
           !is_valid_date(*((int *)selects.conditions[i].right_value.data))) {
            rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
            break;
        }
    }
    if(rc != RC::SUCCESS) {
        snprintf(response, sizeof(response), "FAILURE\n");
        session_event->set_response(response);
        end_trx_if_need(session, trx, false);
        return rc;
    }
    // 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
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
    if (rc != RC::SUCCESS) {
        snprintf(response, sizeof(response), "FAILURE\n");
        session_event->set_response(response);
        for (SelectExeNode *&tmp_node: select_nodes) {
            delete tmp_node;
        }
        end_trx_if_need(session, trx, false);
        return rc;
    }
    output_scheam.set_groupby(selects.groupby_attr, selects.groupby_num, selects.relations[0]);

    // 这里需要将多个tuple_set合成一个tuple_set, 但是这不是最后输出的那个tuple_set
    TupleSet tuple_set;
    if (select_nodes.size() > 1) {
        // 本次查询了多张表，需要做join操作
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
        // 当前只查询一张表，直接返回结果即可
        tuple_set = std::move(tuple_sets.front());
    }

    if (selects.orderbys_num > 0) {
        RC rc = tuple_set.sort(selects);
        if (rc != RC::SUCCESS) {
            snprintf(response, sizeof(response), "FAILURE\n");
            session_event->set_response(response);
            for (SelectExeNode *&select_node: select_nodes) {
                delete select_node;
            }
            end_trx_if_need(session, trx, false);
            return rc;
        }
    }

    if(ret_tupleset!=nullptr){
        TupleSchema ret_output_scheam;
        for (int i = 0; i < selects.attr_num; i++) {
            const RelAttr &attr = selects.attributes[i];
            const char *table_name = attr.relation_name != nullptr ? attr.relation_name : selects.relations[0];
            AttrType attr_type = output_scheam.field(i).type();
            if (attr.aggre_type == AggreType::AVG) {
                attr_type = FLOATS;
            }
            ret_output_scheam.add(attr_type, table_name, attr.attribute_name, attr.aggre_type);
        }
        ret_tupleset->set_schema(output_scheam);
        rc = ret_tupleset->set_tuple_set(std::move(tuple_set));
        ret_tupleset->set_schema(ret_output_scheam);
        if (rc != RC::SUCCESS) {
            snprintf(response, sizeof(response), "FAILURE\n");
            session_event->set_response(response);
            for (SelectExeNode *&tmp_node: select_nodes) {
                delete tmp_node;
            }
            end_trx_if_need(session, trx, false);
            return rc;
        }
    } else {
        TupleSet tuple_set1; //最后输出的tuple_set
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
}

RC ExecuteStage::gen_output_scheam(std::unordered_map<std::string, Table*> &tables_map, 
                const Selects &selects, TupleSchema &output_scheam){

    int attr_num = selects.attr_num;
    for (int i = 0; i < attr_num; i++) {
        const RelAttr &attr = selects.attributes[i];
        if (attr.aggre_type != AggreType::NON) {
            // 聚合属性
            const char *table_name = attr.relation_name != nullptr ? attr.relation_name : selects.relations[0];
            std::string table_name1(table_name);
            AttrType attr_type;
            Table *table = tables_map[table_name1];

            bool is_star_num_float = is_valid_aggre(attr.attribute_name);
            if(!is_star_num_float){  // attribute 
                attr_type = table->table_meta().field(attr.attribute_name)->type();
            } else if (attr.aggre_type == AggreType::COUNT) { 
                // count(1), 直接把他指定为INT,是不是也行？
                // attr_type = table->table_meta().field(0)->type();
                attr_type = AttrType::INTS;
            } else { // min(1)
                return RC::GENERIC_ERROR;
            }
            output_scheam.add(attr_type, table_name, attr.attribute_name, attr.aggre_type);
        } else {
            // 表属性
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

// 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
RC create_selection_executor(Trx *trx, const Selects &selects, Table *table,
                const char *table_name, SelectExeNode &select_node) {
    // 列出跟这张表关联的Attr
    TupleSchema schema;
    /*
    int flag_all_attr = false;

    // 首先把select.attribute里面属性添加到schema
    for (int i = selects.attr_num - 1; i >= 0; i--) {
        const RelAttr &attr = selects.attributes[i];
        if (nullptr == attr.relation_name || 0 == strcmp(table_name, attr.relation_name)) {
            if (0 == strcmp("*", attr.attribute_name) || is_valid_aggre(attr.attribute_name) ) {
                TupleSchema::from_table(table, schema);
                flag_all_attr = true;
                break;
            } else {
                RC rc = RC::SUCCESS;
                rc = schema_add_field(table, attr.attribute_name, schema);
            }
        }
    }

    // 在condition里面相关的属性添加到schema, 例如：
    // select t1.age, t2.name from t1, t2 where t1.id = t2.id;
    // 这时候t1.id 就需要被加入schema，方便后面笛卡尔积过滤
    //
    std::vector<DefaultConditionFilter *> condition_filters;
    for (size_t i = 0; i < selects.condition_num; i++) {
        const Condition &condition = selects.conditions[i];
        if ((condition.left_is_attr == 0 && condition.right_is_attr == 0) || // 两边都是值
            (condition.left_is_attr == 1 && condition.right_is_attr == 0 &&
             match_table(selects, condition.left_attr.relation_name, table_name)) ||  // 左边是属性右边是值
            (condition.left_is_attr == 0 && condition.right_is_attr == 1 &&
             match_table(selects, condition.right_attr.relation_name, table_name)) ||  // 左边是值，右边是属性名
            (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
             match_table(selects, condition.left_attr.relation_name, table_name) &&
             match_table(selects, condition.right_attr.relation_name, table_name)) // 左右都是属性名，并且表名都符合
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
        if (!flag_all_attr) {
            if ((condition.left_is_attr == 1 && condition.right_is_attr == 1) && !flag_all_attr) {
                if (match_table(selects, condition.left_attr.relation_name, table_name) && 
                    !match_table(selects, condition.right_attr.relation_name, table_name)) {
                    // 左右都是属性名，并且有一个和 table_name 相同
                    schema_add_field(talble, condition.left_attr.attribute_name, schema);
                }else if (!match_table(selects, condition.left_attr.relation_name, table_name) && 
                    match_table(selects, condition.right_attr.relation_name, table_name)) {
                    // 左右都是属性名，并且有一个和 table_name 相同
                    schema_add_field(talble, condition.right_attr.attribute_name, schema);
                }
            }
        }
    }*/

    // TODO: group by, order by
    

    if (selects.relation_num > 1 || selects.orderbys_num > 0) {
        // select t1.age from t1, t2 where t1.id = t2.id;
        // 就目前来说，如果查询包括多张表，那需要把每张的表的相关字段(t1.age, t1.id, t2.id)都列出来, 
        // 方便笛卡尔积做过滤。现在是把所有字段都列了出来，这个地方后面可能需要优化。
        TupleSchema::from_table(table, schema);
    } else {
        for (int i = selects.attr_num - 1; i >= 0; i--) {
            const RelAttr &attr = selects.attributes[i];
            if (nullptr == attr.relation_name || 0 == strcmp(table_name, attr.relation_name)) {
                if (0 == strcmp("*", attr.attribute_name) || is_valid_aggre(attr.attribute_name) ) {
                    // 列出这张表所有字段
                    TupleSchema::from_table(table, schema);
                    break; // 没有校验，给出* 之后，再写字段的错误
                } else {
                    // 列出这张表相关字段
                    RC rc = RC::SUCCESS;
                    // if (attr.aggre_type != NON) {
                        rc = schema_add_field(table, attr.attribute_name, schema);
                    // }
                    if (rc != RC::SUCCESS) {
                        return rc;
                    }
                }

            }
        }
        RC rc = RC::SUCCESS;
        for(size_t i = 0; i<selects.groupby_num; i++){
            rc = schema_add_field(table, selects.groupby_attr[i].attribute_name, schema);
        }
        if (rc != RC::SUCCESS) {
            return rc;
        }
    }

    // 找出仅与此表相关的过滤条件, 或者都是值的过滤条件
    std::vector<DefaultConditionFilter *> condition_filters;
    for (size_t i = 0; i < selects.condition_num; i++) {
        const Condition &condition = selects.conditions[i];
        if ((condition.left_type == VALUE && condition.right_type == VALUE) || // 两边都是值
            (condition.left_type == ATTR && condition.right_type == VALUE &&
             match_table(selects, condition.left_attr.relation_name, table_name)) ||  // 左边是属性右边是值
            (condition.left_type == VALUE && condition.right_type == ATTR &&
             match_table(selects, condition.right_attr.relation_name, table_name)) ||  // 左边是值，右边是属性名
            (condition.left_type == ATTR && condition.right_type == ATTR &&
             match_table(selects, condition.left_attr.relation_name, table_name) &&
             match_table(selects, condition.right_attr.relation_name, table_name)) // 左右都是属性名，并且表名都符合
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
    tuple_set.set_schema(scheam);

    std::list<const Condition *> conditions;
    for (size_t i = 0; i < selects.condition_num; i++) {
        const Condition &condition = selects.conditions[i];
        if (condition.left_type == ATTR && condition.right_type == ATTR &&
            0 != strcmp(condition.left_attr.relation_name, condition.right_attr.relation_name)) {
            conditions.push_back(&condition);
        }
    }
    
    std::list<const Condition *> match_conditions;
    std::vector<std::vector<const Condition*>> conditions_group(tuple_sets.size());
    gen_conditions_group(conditions, match_conditions, conditions_group, tuple_sets, tuple_sets.size() - 1);

    std::unordered_map<std::string, const Tuple*> tuples_map;
    return do_cross_join(tuple_sets, tuple_sets.size() - 1, conditions_group, tuple_set, tuples_map, schemas_map);
}

void gen_conditions_group(std::list<const Condition *> &conditions,
                            std::list<const Condition *> &match_conditions,
                            std::vector<std::vector<const Condition*>> &conditions_group,
                            std::vector<TupleSet> &tuple_sets, 
                            int index) {
    if (index == -1) {
        return;
    }

    const TupleSet &tuple_set = tuple_sets[index];
    const std::vector<TupleField> &fields = tuple_set.get_schema().fields();
    std::string table_name(fields[0].table_name());

    for (auto iter = match_conditions.begin(); iter != match_conditions.end();) {
        auto tmp = iter;
        iter++;
        std::string left_table((*tmp)->left_attr.relation_name);
        std::string right_table((*tmp)->right_attr.relation_name);
        if (left_table == table_name || right_table == table_name) {
            conditions_group[index].push_back(*tmp);
            match_conditions.erase(tmp);
        }
    }
    for (auto iter = conditions.begin(); iter != conditions.end();) {
        auto tmp = iter;
        iter++;
        std::string left_table((*tmp)->left_attr.relation_name);
        std::string right_table((*tmp)->right_attr.relation_name);
        if (left_table == table_name || right_table == table_name) {
            match_conditions.push_back(*tmp);
            conditions.erase(tmp);
        }
    }
    gen_conditions_group(conditions, match_conditions, conditions_group, tuple_sets, index - 1);
}

RC do_cross_join(std::vector<TupleSet> &tuple_sets, int index, 
                    std::vector<std::vector<const Condition *>> &conditions_group,
                    TupleSet &tuple_set, 
                    std::unordered_map<std::string, const Tuple*> &tuples_map,
                    std::unordered_map<std::string, const TupleSchema*> &schemas_map) {

    if (index == -1) {
        Tuple new_tuple;
        // TODO: 这个地方可以优化
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
    const std::vector<Tuple> &tuples = tuple_set1.tuples();
    const std::vector<TupleField> &fields = tuple_set1.get_schema().fields();
    std::string table_name(fields[0].table_name());

    int size = tuples.size();
    for (int i = 0; i < size; i++) {
        tuples_map[table_name] = &tuples[i];
        if (do_filter(conditions_group[index], tuples_map, schemas_map)) {
            RC rc = do_cross_join(tuple_sets, index - 1, conditions_group, tuple_set, tuples_map, schemas_map);
            if (rc != RC::SUCCESS) {
                return rc;
            }
        }
    }

    return RC::SUCCESS;
}

static bool do_filter(std::vector<const Condition *> &conditions, 
                    std::unordered_map<std::string, const Tuple*> &tuples_map,
                    std::unordered_map<std::string, const TupleSchema*> &schemas_map) {

    for (auto &condition : conditions) {
        std::string left_table(condition->left_attr.relation_name);
        std::string right_table(condition->right_attr.relation_name);
        char *left_attr = condition->left_attr.attribute_name;
        char *right_attr = condition->right_attr.attribute_name;

        int i = schemas_map[left_table]->index_of_field(left_table.c_str(), left_attr);
        int j = schemas_map[right_table]->index_of_field(right_table.c_str(), right_attr);
        if ( i == -1 || j == -1) {
            return false;
        }
        const TupleValue &tuple_value1 = tuples_map[left_table]->get(i);
        const TupleValue &tuple_value2 = tuples_map[right_table]->get(j);

        bool left_is_null = tuple_value1.is_null();
        bool right_is_null = tuple_value2.is_null();

        if (left_is_null && right_is_null) {
            if (!(condition->comp == IS_COMPOP)) {
                return false;
            }
        } else if (left_is_null || right_is_null) {
            if (!(condition->comp == IS_NOT_COMPOP)) {
               return false;
            }
        } else {  // notnull comop notnull
            int result = tuple_value1.compare(tuple_value2);
            if ((result == 0 && (condition->comp == CompOp::EQUAL_TO || condition->comp == CompOp::GREAT_EQUAL ||
                                condition->comp == CompOp::LESS_EQUAL)) ||
                (result == 1 && (condition->comp == CompOp::GREAT_THAN || condition->comp == CompOp::GREAT_EQUAL ||
                                condition->comp == CompOp::NOT_EQUAL)) ||
                (result == -1 && (condition->comp == CompOp::LESS_THAN || condition->comp == CompOp::LESS_EQUAL ||
                                condition->comp == CompOp::NOT_EQUAL))) {
                // do nothing
            } else {
                return false;
            }
        }
    }

    return true;
}
