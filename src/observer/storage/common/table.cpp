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
// Created by Wangyunlai on 2021/5/13.
//

#include <limits.h>
#include <memory>
#include <string.h>
#include <algorithm>
#include<iostream>

#include <cstring>
#include<sstream>
#include<fstream>
#include <vector>
#include "storage/common/table.h"
#include "storage/common/table_meta.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/default/disk_buffer_pool.h"
#include "storage/common/record_manager.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/common/index.h"
#include "storage/common/bplus_tree_index.h"
#include "storage/trx/trx.h"

Table::Table() :
        data_buffer_pool_(nullptr),
        file_id_(-1),
        record_handler_(nullptr) {
}

Table::~Table() {
    delete record_handler_;
    record_handler_ = nullptr;

    if (data_buffer_pool_ != nullptr && file_id_ >= 0) {
        data_buffer_pool_->close_file(file_id_);
        data_buffer_pool_ = nullptr;
    }

    LOG_INFO("Table has been closed: %s", name());
}

RC Table::create(const char *path, const char *name, const char *base_dir, int attribute_count,
                 const AttrInfo attributes[]) {

    if (nullptr == name || common::is_blank(name)) {
        LOG_WARN("Name cannot be empty");
        return RC::INVALID_ARGUMENT;
    }
    LOG_INFO("Begin to create table %s:%s", base_dir, name);

    if (attribute_count <= 0 || nullptr == attributes) {
        LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d, attributes=%p",
                 name, attribute_count, attributes);
        return RC::INVALID_ARGUMENT;
    }

    RC rc = RC::SUCCESS;

    // 使用 table_name.table记录一个表的元数据
    // 判断表文件是否已经存在

    int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
    if (-1 == fd) {
        if (EEXIST == errno) {
            LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s",
                      path, strerror(errno));
            return RC::SCHEMA_TABLE_EXIST;
        }
        LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s",
                  path, errno, strerror(errno));
        return RC::IOERR;
    }

    close(fd);

    // 创建文件
    if ((rc = table_meta_.init(name, attribute_count, attributes)) != RC::SUCCESS) {
        LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
        return rc; // delete table file
    }

    std::fstream fs;
    fs.open(path, std::ios_base::out | std::ios_base::binary);
    if (!fs.is_open()) {
        LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
        return RC::IOERR;
    }

    // 记录元数据到文件中
    table_meta_.serialize(fs);
    fs.close();

    std::string data_file = std::string(base_dir) + "/" + name + TABLE_DATA_SUFFIX;
    data_buffer_pool_ = theGlobalDiskBufferPool();
    rc = data_buffer_pool_->create_file(data_file.c_str());
    if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
        return rc;
    }

    rc = init_record_handler(base_dir);

    base_dir_ = base_dir;
    LOG_INFO("Successfully create table %s:%s", base_dir, name);
    return rc;
}

// tzh add here:
RC Table::drop(const char *path, const char *name, const char *base_dir) {
    if (nullptr == name || common::is_blank(name)) {
        LOG_WARN("Name cannot be empty");
        return RC::INVALID_ARGUMENT;
    }
    LOG_INFO("Begin to drop table %s:%s", base_dir, name);
    RC rc = RC::SUCCESS;

    // remove index files
    const int index_num = table_meta_.index_num();
    for (int i = 0; i < index_num; i++) {
        const IndexMeta *index_meta = table_meta_.index(i);

        // close index
        Index *index = find_index(index_meta->name());
        if (nullptr != index) {
            // index.close()
            delete index;
        }

        /*
         * 这段语句好像没啥用
        const FieldMeta *field_meta = table_meta_.field(index_meta->field());
        if (field_meta == nullptr) {
            LOG_PANIC("Found invalid index meta info which has a non-exists field. table=%s, index=%s, field=%s",
                      name, index_meta->name(), index_meta->field());
            return RC::GENERIC_ERROR;
        }
        */

        std::string index_file = index_data_file(base_dir, name, index_meta->name());
        if (remove(index_file.c_str()) != 0) {
            LOG_ERROR("Fail to remove file %s, due to %s.", name, strerror(errno));
            return RC::IOERR_DELETE;
        }
    }

    LOG_INFO("Successfully drop index file of %s:%s", base_dir, name);
    return rc;
}

RC Table::open(const char *meta_file, const char *base_dir) {
    // 加载元数据文件
    std::fstream fs;
    std::string meta_file_path = std::string(base_dir) + "/" + meta_file;
    fs.open(meta_file_path, std::ios_base::in | std::ios_base::binary);
    if (!fs.is_open()) {
        LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file, strerror(errno));
        return RC::IOERR;
    }
    if (table_meta_.deserialize(fs) < 0) {
        LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file);
        return RC::GENERIC_ERROR;
    }
    fs.close();

    // 加载数据文件
    RC rc = init_record_handler(base_dir);

    base_dir_ = base_dir;

    const int index_num = table_meta_.index_num();
    for (int i = 0; i < index_num; i++) {
        const IndexMeta *index_meta = table_meta_.index(i);
        const char* field_name = index_meta->field();
        std::vector<const FieldMeta*> fields_meta;
        // index 的 field 可能包含多列， field_name 由多个列名字通过 "-" 链组成。
        // 解析field_name，拿到列名。
        int j = 0;
        while (1) {
            char tmp[256];
            while(field_name[j] != '\0' && field_name[j] != '-') {
                tmp[j] = field_name[j];
                j++;
            }
            tmp[j] = '\0';
            const FieldMeta* field_meta = table_meta_.field(tmp);
            if (field_meta == nullptr) {
                LOG_PANIC("Found invalid index meta info which has a non-exists field. table=%s, index=%s, field=%s",
                      name(), index_meta->name(), index_meta->field());
                return RC::GENERIC_ERROR;
            }
            fields_meta.push_back(field_meta);

            if (field_name[j] == '\0') {
                break;
            }
            j++;
        }

        BplusTreeIndex *index = new BplusTreeIndex();
        std::string index_file = index_data_file(base_dir, name(), index_meta->name());
        rc = index->open(index_file.c_str(), *index_meta, fields_meta);
        if (rc != RC::SUCCESS) {
            delete index;
            LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%d:%s",
                      name(), index_meta->name(), index_file.c_str(), rc, strrc(rc));
            return rc;
        }
        indexes_.push_back(index);
    }
    return rc;
}

RC Table::commit_insert(Trx *trx, const RID &rid) {
    Record record;
    RC rc = record_handler_->get_record(&rid, &record);
    if (rc != RC::SUCCESS) {
        return rc;
    }

    return trx->commit_insert(this, record);
}

RC Table::rollback_insert(Trx *trx, const RID &rid) {

    Record record;
    RC rc = record_handler_->get_record(&rid, &record);
    if (rc != RC::SUCCESS) {
        return rc;
    }

    // remove all indexes
    rc = delete_entry_of_indexes(record.data, rid, false);
    if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to delete indexes of record(rid=%d.%d) while rollback insert, rc=%d:%s",
                  rid.page_num, rid.slot_num, rc, strrc(rc));
    } else {
        rc = record_handler_->delete_record(&rid);
    }
    return rc;
}

RC Table::insert_record(Trx *trx, Record *record) {
    RC rc = RC::SUCCESS;

    if (trx != nullptr) {
        trx->init_trx_info(this, *record);
    }
    if (insert_unique_conflict(record->data)) {
        return RC::CONSTRAINT_UNIQUE;
    }

    rc = record_handler_->insert_record(record->data, table_meta_.record_size(), &record->rid);
    if (rc != RC::SUCCESS) {
        LOG_ERROR("Insert record failed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));
        return rc;
    }

    if (trx != nullptr) {
        rc = trx->insert_record(this, record);
        if (rc != RC::SUCCESS) {
            LOG_ERROR("Failed to log operation(insertion) to trx");

            RC rc2 = record_handler_->delete_record(&record->rid);
            if (rc2 != RC::SUCCESS) {
                LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                          name(), rc2, strrc(rc2));
            }
            return rc;
        }
    }

    rc = insert_entry_of_indexes(record->data, record->rid);
    if (rc != RC::SUCCESS) {
        RC rc2 = delete_entry_of_indexes(record->data, record->rid, true);
        if (rc2 != RC::SUCCESS) {
            LOG_PANIC("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                      name(), rc2, strrc(rc2));
        }

        rc2 = record_handler_->delete_record(&record->rid);
        if (rc2 != RC::SUCCESS) {
            LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                      name(), rc2, strrc(rc2));
        }
        return rc;
    }
    return rc;
}

RC Table::mulit_insert_record(Trx *trx, int value_num, const Value *values, std::vector<Record> &trash) {
    if (value_num <= 0 || nullptr == values) {
        LOG_ERROR("Invalid argument. value num=%d, values=%p", value_num, values);
        return RC::INVALID_ARGUMENT;
    }

    char *record_data;
    RC rc = make_record(value_num, values, record_data);
    if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to create a record. rc=%d:%s", rc, strrc(rc));
        return rc;
    }

    Record record;
    record.data = record_data;

    // record.valid = true;
    rc = insert_record(trx, &record);
    trash.push_back(record);
    if (rc != RC::SUCCESS) {
        trash.pop_back();
    }
    delete[] record_data;
    return rc;
}

RC Table::insert_record(Trx *trx, int value_num, const Value *values) {
    if (value_num <= 0 || nullptr == values) {
        LOG_ERROR("Invalid argument. value num=%d, values=%p", value_num, values);
        return RC::INVALID_ARGUMENT;
    }

    char *record_data;
    RC rc = make_record(value_num, values, record_data);
    if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to create a record. rc=%d:%s", rc, strrc(rc));
        return rc;
    }

    Record record;
    record.data = record_data;
    // record.valid = true;
    rc = insert_record(trx, &record);
    delete[] record_data;
    return rc;
}

const char *Table::name() const {
    return table_meta_.name();
}

class IndexInserter {
public:
    explicit IndexInserter(Index *index) : index_(index) {
    }

    RC insert_index(const Record *record) {
        return index_->insert_entry(record->data, &record->rid);
    }

    Index *get_index() {
        return index_;
    }

private:
    Index *index_;
};

const TableMeta &Table::table_meta() const {
    return table_meta_;
}


RC Table::make_record(int value_num, const Value *values, char *&record_out) {
    // 检查字段类型是否一致
    if (value_num + table_meta_.sys_field_num() != table_meta_.field_num()) {
        return RC::SCHEMA_FIELD_MISSING;
    }

    const int normal_field_start_index = table_meta_.sys_field_num();
    std::vector<bool> fields_nullable;
    table_meta_.fields_nullable_type(fields_nullable);
    for (int i = 0; i < value_num; i++) {
        const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
        Value &value = const_cast<Value &>(values[i]);
        if (field->type() != value.type && NULLS != value.type &&
            field->type() != TEXTS) {  // NULLS type can match any type
            LOG_ERROR("Invalid value type. field name=%s, type=%d, but given=%d",
                      field->name(), field->type(), value.type);
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
        if (field->type() == TEXTS && value.type == CHARS) {
            value.type = TEXTS;
            char text[4097];
            char *val = static_cast<char *>(value.data);
            if (strlen(val) > 4096) {
                std::strncpy(text, static_cast<char *>(value.data), 4096);
            } else {
                strcpy(text , static_cast<char *>(value.data));
            }
//           std:: string out;
            std::ostringstream os;
            {
                os << text << std::endl;
            }
            int a = rand();
            int b = rand();
            int c = rand();
            int key = a * 99 + b * 9 + c;
            const char *name = "text";
            std::string path = name;
            std::ofstream fout(
                    "./miniob/db/sys/" + std::string(const_cast<char *>(table_meta_.name())) + "_" +
                    std::to_string(key) + "_" +
                    path + ".txt");
            if (fout) {
                //将out流转换为string类型，写入到文件流中
                fout << os.str() << std::endl;
                fout.close();
            }
            value.data = static_cast<void *>(&key);
        }
        if (NULLS == value.type && fields_nullable[i] == false) {
            LOG_ERROR("fields not nullable. field name=%s, type=%d, but given=%d",
                      field->name(), field->type(), value.type);
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
    }

    // 复制所有字段的值
    int record_size = table_meta_.record_size();
    char *record = new char[record_size];

    for (int i = 0; i < value_num; i++) {
        const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
        const Value &value = values[i];
        std::string data = (char *) (value.data);
        // std::transform(data.begin(), data.end(), ::tolower);
        memcpy(record + field->offset(), value.data, field->len());
    }

    record_out = record;
    return RC::SUCCESS;
}

RC Table::init_record_handler(const char *base_dir) {
    std::string data_file = std::string(base_dir) + "/" + table_meta_.name() + TABLE_DATA_SUFFIX;
    if (nullptr == data_buffer_pool_) {
        data_buffer_pool_ = theGlobalDiskBufferPool();
    }

    int data_buffer_pool_file_id;
    RC rc = data_buffer_pool_->open_file(data_file.c_str(), &data_buffer_pool_file_id);
    if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s",
                  data_file.c_str(), rc, strrc(rc));
        return rc;
    }

    record_handler_ = new RecordFileHandler();
    rc = record_handler_->init(*data_buffer_pool_, data_buffer_pool_file_id);
    if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to init record handler. rc=%d:%s", rc, strrc(rc));
        return rc;
    }

    file_id_ = data_buffer_pool_file_id;
    return rc;
}

/**
 * 为了不把Record暴露出去，封装一下
 */
class RecordReaderScanAdapter {
public:
    explicit RecordReaderScanAdapter(void (*record_reader)(const char *data, void *context), void *context)
            : record_reader_(record_reader), context_(context) {
    }

    void consume(const Record *record) {
        record_reader_(record->data, context_);
    }

private:
    void (*record_reader_)(const char *, void *);

    void *context_;
};

static RC scan_record_reader_adapter(Record *record, void *context) {
    RecordReaderScanAdapter &adapter = *(RecordReaderScanAdapter *) context;
    adapter.consume(record);
    return RC::SUCCESS;
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context,
                      void (*record_reader)(const char *data, void *context)) {
    RecordReaderScanAdapter adapter(record_reader, context);
    return scan_record(trx, filter, limit, (void *) &adapter, scan_record_reader_adapter);
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context,
                      RC (*record_reader)(Record *record, void *context)) {
    if (nullptr == record_reader) {
        return RC::INVALID_ARGUMENT;
    }

    if (0 == limit) {
        return RC::SUCCESS;
    }

    if (limit < 0) {
        limit = INT_MAX;
    }

    /*
     * 暂时不适用 index scanner
    IndexScanner *index_scanner = find_index_for_scan(filter);
    if (index_scanner != nullptr) {
        return scan_record_by_index(trx, index_scanner, filter, limit, context, record_reader);
    } 
    */

    RC rc = RC::SUCCESS;
    RecordFileScanner scanner;
    rc = scanner.open_scan(*data_buffer_pool_, file_id_, filter);
    if (rc != RC::SUCCESS) {
        LOG_ERROR("failed to open scanner. file id=%d. rc=%d:%s", file_id_, rc, strrc(rc));
        return rc;
    }

    int record_count = 0;
    Record record;
    rc = scanner.get_first_record(&record);
    for (; RC::SUCCESS == rc && record_count < limit; rc = scanner.get_next_record(&record)) {
        if (trx == nullptr || trx->is_visible(this, &record)) {
            rc = record_reader(&record, context);
            if (rc != RC::SUCCESS) {
                break;
            }
            record_count++;
        }
    }

    if (RC::RECORD_EOF == rc) {
        rc = RC::SUCCESS;
    } else {
        LOG_ERROR("failed to scan record. file id=%d, rc=%d:%s", file_id_, rc, strrc(rc));
    }
    scanner.close_scan();
    return rc;
}

RC Table::scan_record_by_index(Trx *trx, IndexScanner *scanner, ConditionFilter *filter, int limit, void *context,
                               RC (*record_reader)(Record *, void *)) {
    RC rc = RC::SUCCESS;
    RID rid;
    Record record;
    int record_count = 0;
    while (record_count < limit) {
        rc = scanner->next_entry(&rid);
        if (rc != RC::SUCCESS) {
            if (RC::RECORD_EOF == rc || RC::RECORD_NO_MORE_IDX_IN_MEM == rc) {
                rc = RC::SUCCESS;
                break;
            }
            LOG_ERROR("Failed to scan table by index. rc=%d:%s", rc, strrc(rc));
            break;
        }

        rc = record_handler_->get_record(&rid, &record);
        if (rc != RC::SUCCESS) {
            LOG_ERROR("Failed to fetch record of rid=%d:%d, rc=%d:%s", rid.page_num, rid.slot_num, rc, strrc(rc));
            break;
        }

        if ((trx == nullptr || trx->is_visible(this, &record)) && (filter == nullptr || filter->filter(record))) {
            rc = record_reader(&record, context);
            if (rc != RC::SUCCESS) {
                LOG_TRACE("Record reader break the table scanning. rc=%d:%s", rc, strrc(rc));
                break;
            }
        }

        record_count++;
    }

    scanner->destroy();
    return rc;
}


static RC insert_index_record_reader_adapter(Record *record, void *context) {
    IndexInserter &inserter = *(IndexInserter *) context;

    return inserter.insert_index(record);
}

/*
RC Table::create_index(Trx *trx, const char *index_name, const char *attribute_name, const int &is_unique) {

    if (index_name == nullptr || common::is_blank(index_name) ||
        attribute_name == nullptr || common::is_blank(attribute_name)) {
        return RC::INVALID_ARGUMENT;
    }
    if (table_meta_.index(index_name) != nullptr ||
        table_meta_.find_index_by_field((attribute_name))) {
        return RC::SCHEMA_INDEX_EXIST;
    }

    const FieldMeta *field_meta = table_meta_.field(attribute_name);
    if (!field_meta) {
        return RC::SCHEMA_FIELD_MISSING;
    }

    IndexMeta new_index_meta;
    RC rc = new_index_meta.init(index_name, *field_meta, is_unique);
    if (rc != RC::SUCCESS) {
        return rc;
    }

    // 创建索引相关数据
    BplusTreeIndex *index = new BplusTreeIndex();
    std::string index_file = index_data_file(base_dir_.c_str(), name(), index_name);
    rc = index->create(index_file.c_str(), new_index_meta, *field_meta);
    if (rc != RC::SUCCESS) {
        delete index;
        LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
        return rc;
    }

    // 遍历当前的所有数据，插入这个索引
    IndexInserter index_inserter(index);
    rc = scan_record(trx, nullptr, -1, &index_inserter, insert_index_record_reader_adapter);
    if (rc != RC::SUCCESS) {
        // rollback
        delete index;
        LOG_ERROR("Failed to insert index to all records. table=%s, rc=%d:%s", name(), rc, strrc(rc));
        return rc;
    }
    indexes_.push_back(index);
    TableMeta new_table_meta(table_meta_);
    rc = new_table_meta.add_index(new_index_meta);
    if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
        return rc;
    }
    // 创建元数据临时文件
    std::string tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
    std::fstream fs;
    fs.open(tmp_file, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
    if (!fs.is_open()) {
        LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
        return RC::IOERR; // 创建索引中途出错，要做还原操作
    }
    if (new_table_meta.serialize(fs) < 0) {
        LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
        return RC::IOERR;
    }
    fs.close();

    // 覆盖原始元数据文件
    std::string meta_file = table_meta_file(base_dir_.c_str(), name());
    int ret = rename(tmp_file.c_str(), meta_file.c_str());
    if (ret != 0) {
        LOG_ERROR(
                "Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). " \
              "system error=%d:%s", tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
        return RC::IOERR;
    }

    table_meta_.swap(new_table_meta);

    LOG_INFO("add a new index (%s) on the table (%s)", index_name, name());


    return rc;
} */

RC Table::create_index(Trx *trx, const char *index_name, const char *const attributes_name[], int attribute_num, const int &is_unique) {
    // 检查参数
    if (index_name == nullptr || common::is_blank(index_name)) {
        return RC::INVALID_ARGUMENT;
    }

    for (int i = 0; i < attribute_num; i++) {
        const char* attribute_name = attributes_name[i];
        if (attribute_name == nullptr || common::is_blank(attribute_name)) {
            return RC::INVALID_ARGUMENT;
        }
    }

    // 合成field_name
    int name_lens = 0;
    for (int i = attribute_num - 1; i >= 0; i--) {
        name_lens += (strlen(attributes_name[i]) + 1);
    }
    std::unique_ptr<char> field_name(new char[name_lens + 1]);
    char* field_name_ptr = field_name.get();
    name_lens = 0;
    for (int i = attribute_num - 1; i >= 0; i--) {
        int name_len = strlen(attributes_name[i]);
        strncpy(field_name_ptr + name_lens, attributes_name[i], name_len);
        name_lens += name_len;
        field_name_ptr[name_lens] = '-';
        name_lens += 1;
    }
    field_name_ptr[name_lens - 1] = '\0';

    // 检查索引是否存在
    if (table_meta_.index(index_name) != nullptr ||
        table_meta_.find_index_by_field((field_name_ptr))) {
        return RC::SCHEMA_INDEX_EXIST;
    }

    // 创建索引相关数据
    IndexMeta new_index_meta;
    RC rc = new_index_meta.init(index_name, field_name_ptr, is_unique);
    if (rc != RC::SUCCESS) {
        return rc;
    }

    std::vector<const FieldMeta*> fields_meta;
    for (int i = attribute_num - 1; i >= 0; i--) {
        const FieldMeta *field_meta = table_meta_.field(attributes_name[i]);
        if (!field_meta) {
            return RC::SCHEMA_FIELD_MISSING;
        }
        fields_meta.push_back(field_meta);
    }

    BplusTreeIndex *index = new BplusTreeIndex();
    std::string index_file = index_data_file(base_dir_.c_str(), name(), index_name);
    rc = index->create(index_file.c_str(), new_index_meta, fields_meta);
    if (rc != RC::SUCCESS) {
        delete index;
        LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
        return rc;
    }

    // 遍历当前的所有数据，插入这个索引
    IndexInserter index_inserter(index);
    rc = scan_record(trx, nullptr, -1, &index_inserter, insert_index_record_reader_adapter);
    if (rc != RC::SUCCESS) {
        // rollback
        delete index;
        LOG_ERROR("Failed to insert index to all records. table=%s, rc=%d:%s", name(), rc, strrc(rc));
        return rc;
    }
    indexes_.push_back(index);
    TableMeta new_table_meta(table_meta_);
    rc = new_table_meta.add_index(new_index_meta);
    if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
        return rc;
    }
    // 创建元数据临时文件
    std::string tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
    std::fstream fs;
    fs.open(tmp_file, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
    if (!fs.is_open()) {
        LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
        return RC::IOERR; // 创建索引中途出错，要做还原操作
    }
    if (new_table_meta.serialize(fs) < 0) {
        LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
        return RC::IOERR;
    }
    fs.close();

    // 覆盖原始元数据文件
    std::string meta_file = table_meta_file(base_dir_.c_str(), name());
    int ret = rename(tmp_file.c_str(), meta_file.c_str());
    if (ret != 0) {
        LOG_ERROR(
                "Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). " \
              "system error=%d:%s", tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
        return RC::IOERR;
    }

    table_meta_.swap(new_table_meta);

    LOG_INFO("add a new index (%s) on the table (%s)", index_name, name());


    return rc;
}


class RecordUpdater {
public:
    RecordUpdater(Table &table, Trx *trx, const char *attribute_name, const Value *value) :
            table_(table), trx_(trx), attribute_name_(attribute_name), value_(value) {
    }

    RC update_record(Record *record) {
        RC rc = RC::SUCCESS;
        rc = table_.update_record(trx_, record, attribute_name_, value_);
        if (rc == RC::SUCCESS) {
            updated_count_++;
        }
        return rc;
    }

    int updated_count() const {
        return updated_count_;
    }

private:
    Table &table_;
    Trx *trx_;
    const char *attribute_name_;
    const Value *value_;
    int updated_count_ = 0;
};

static RC record_reader_update_adapter(Record *record, void *context) {
    RecordUpdater &record_updater = *(RecordUpdater *) context;
    return record_updater.update_record(record);
}

RC Table::update_record(Trx *trx, ConditionFilter *filter, const char *attribute_name, const Value *value,
                        int *updated_count) {
    RecordUpdater updater(*this, trx, attribute_name, value);
    RC rc = scan_record(trx, filter, -1, &updater, record_reader_update_adapter);
    if (updated_count != nullptr) {
        *updated_count = updater.updated_count();
    }
    return rc;
}

RC Table::update_record(Trx *trx, Record *record, const char *attribute_name, const Value *value) {
    RC rc = RC::SUCCESS;
    Record record_new;
    record_new.rid = record->rid;
    char *record_data = record->data;
    const FieldMeta *field = table_meta_.field(attribute_name);
    if (field == nullptr) {
        LOG_ERROR("Invalid field name.Wrong field name=%s", attribute_name);
        return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    if (field->type() != value->type && !(field->type() == TEXTS && value->type == CHARS)) {
        LOG_ERROR("Invalid value type. field name=%s, type=%d, but given=%d",
                  field->name(), field->type(), value->type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
    if (field->type() == TEXTS) {
        int num = *(int *) (record_data + field->offset());
        // value->data 写入文件
        // value->data 赋值文件名
        std::string path =
                "./miniob/db/sys/" + std::string(const_cast<char *>(table_meta_.name())) + "_" + std::to_string(num) +
                "_" + "text.txt";
        std::ofstream fout(path, std::ios::trunc);
        fout << static_cast<char *>(value->data);
        memcpy(record_data + field->offset(), static_cast<void *>(&num), field->len());
        record_new.data = record_data;
        rc = record_handler_->update_record(&record_new);
        return rc;

    }
    memcpy(record_data + field->offset(), value->data, field->len());
    record_new.data = record_data;
    rc = record_handler_->update_record(&record_new);
    return rc;
}

// RC Table::update_record(Trx *trx, const char *attribute_name, const Value *value, int condition_num,
//                         const Condition conditions[], int *updated_count) {
//     // todo: no use of RecodeUpdater; no trx replemented

//     RC rc = RC::SUCCESS;
//     CompositeConditionFilter filter;
//     rc = filter.init(*this, conditions, condition_num);
//     if (rc != RC::SUCCESS) {
//         LOG_ERROR("filter init failed");
//         return RC::GENERIC_ERROR;
//     }
//     *updated_count = 0;
//     int limit = INT_MAX;  // no limit
//     Record record;
//     const int normal_field_start_index = table_meta_.sys_field_num();
//     int value_num = table_meta_.field_num() - table_meta_.sys_field_num();

//     // find the index of attribute_name in an entry.data
//     int record_size = table_meta_.record_size();
//     int attr_index;
//     for (attr_index = 0; attr_index < value_num; attr_index++) {
//         if (0 == strcmp(table_meta_.field(attr_index + normal_field_start_index)->name(), attribute_name)) {
//             break;
//         }
//     }

//     if (value_num <= 0 || nullptr == value ||
//         table_meta_.field(attr_index + normal_field_start_index)->type() != value->type && NULLS != value->type) {
//         LOG_ERROR("Invalid argument. value num=%d, value=%p", value_num, value);
//         return RC::INVALID_ARGUMENT;
//     }

//     std::string data = (char *)(value->data);
//     // std::transform(data.begin(), data.end(), ::tolower);
//     if(data=="!null"){
//         if (table_meta_.field(attr_index + normal_field_start_index)->nullable()==false){
//             return RC::CONSTRAINT_NOTNULL;
//         }
//     }

//     // construct index_scanner
//     IndexScanner *index_scanner = find_index_for_scan(&filter);

//     if (index_scanner != nullptr) { // scan by index
//         RID rid;
//         // update each entry
//         while (*updated_count < limit) {
//             rc = index_scanner->next_entry(&rid);
//             if (rc != RC::SUCCESS) {
//                 if (RC::RECORD_EOF == rc) {  // finish updating all entries
//                     rc = RC::SUCCESS;
//                     break;
//                 }
//                 LOG_ERROR("Failed to scan table by index. rc=%d:%s", rc, strrc(rc));
//                 break;
//             }

//             // get record
//             rc = record_handler_->get_record(&rid, &record);
//             if (rc != RC::SUCCESS) {
//                 LOG_ERROR("Failed to fetch record of rid=%d:%d, rc=%d:%s", rid.page_num, rid.slot_num, rc, strrc(rc));
//                 break;
//             }

//             // a second time filter for check, maybe can delete the last part of this line:
//             if ((trx == nullptr || trx->is_visible(this, &record)) && (filter.filter(record))) {
//                 // rc = record_reader(&record, context);

//                 //construct "new_record" for this entry
//                 char *new_record_data = new char[record_size];

//                 for (int i = 0; i < value_num; i++) {
//                     const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
//                     if (i == attr_index)  // assign value
//                         memcpy(new_record_data + field->offset(), value->data, field->len());
//                     else              // assign record->data
//                         memcpy(new_record_data + field->offset(), record.data + field->offset(), field->len());
//                 }

//                 Record new_record;
//                 new_record.data = new_record_data;
//                 new_record.rid = rid;

//                 rc = delete_entry_of_indexes(record.data, rid, false);  // if not exist this index, don't return err
//                 if (rc != RC::SUCCESS) {
//                     LOG_TRACE("Record reader break the table scanning1. rc=%d:%s", rc, strrc(rc));
//                     break;
//                 }
//                 rc = insert_entry_of_indexes(new_record.data, rid);
//                 if (rc != RC::SUCCESS) {
//                     LOG_TRACE("Record reader break the table scanning2. rc=%d:%s", rc, strrc(rc));
//                     break;
//                 }

//                 // update
//                 rc = record_handler_->update_record(&new_record);

//                 if (rc != RC::SUCCESS) {
//                     LOG_TRACE("Record reader break the table scanning3. rc=%d:%s", rc, strrc(rc));
//                     break;
//                 }
//             }
//             (*updated_count)++;
//         }
//         // todo: update index?
//         index_scanner->destroy();
//     } else { // no index, use record file scanner
//         RecordFileScanner scanner;
//         rc = scanner.open_scan(*data_buffer_pool_, file_id_, &filter);
//         if (rc != RC::SUCCESS) {
//             LOG_ERROR("failed to open scanner. file id=%d. rc=%d:%s", file_id_, rc, strrc(rc));
//             return rc;
//         }

//         rc = scanner.get_first_record(&record);
//         for (; RC::SUCCESS == rc && (*updated_count) < limit; rc = scanner.get_next_record(&record)) {
//             if (trx == nullptr || trx->is_visible(this, &record)) {
//                 //construct "new_record" for this entry
//                 char *new_record_data = new char[record_size];

//                 for (int i = 0; i < value_num; i++) {
//                     const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
//                     if (i == attr_index)  // assign value
//                         memcpy(new_record_data + field->offset(), value->data, field->len());
//                     else              // assign record->data
//                         memcpy(new_record_data + field->offset(), record.data + field->offset(), field->len());
//                 }

//                 Record new_record;
//                 new_record.data = new_record_data;
//                 new_record.rid = record.rid;


//                 rc = delete_entry_of_indexes(record.data, record.rid,
//                                              false);  // if not exist this index, don't return err
//                 if (rc != RC::SUCCESS) {
//                     LOG_TRACE("Record reader break the table scanning1. rc=%d:%s", rc, strrc(rc));
//                     break;
//                 }
//                 rc = insert_entry_of_indexes(new_record.data, record.rid);
//                 if (rc != RC::SUCCESS) {
//                     LOG_TRACE("Record reader break the table scanning2. rc=%d:%s", rc, strrc(rc));
//                     break;
//                 }
//                 // update
//                 rc = record_handler_->update_record(&new_record);

//                 if (rc != RC::SUCCESS) {
//                     LOG_TRACE("Record reader break the table scanning. rc=%d:%s", rc, strrc(rc));
//                     break;
//                 }
//             }
//             (*updated_count)++;
//         }

//         if (RC::RECORD_EOF == rc) {
//             rc = RC::SUCCESS;
//         } else {
//             LOG_ERROR("failed to scan record. file id=%d, rc=%d:%s", file_id_, rc, strrc(rc));
//         }
//         scanner.close_scan();
//     }
//     return rc;
// }

class RecordDeleter {
public:
    RecordDeleter(Table &table, Trx *trx) : table_(table), trx_(trx) {
    }

    RC delete_record(Record *record) {
        RC rc = RC::SUCCESS;
        rc = table_.delete_record(trx_, record);
        if (rc == RC::SUCCESS) {
            deleted_count_++;
        }
        return rc;
    }

    int deleted_count() const {
        return deleted_count_;
    }

private:
    Table &table_;
    Trx *trx_;
    int deleted_count_ = 0;
};

static RC record_reader_delete_adapter(Record *record, void *context) {
    RecordDeleter &record_deleter = *(RecordDeleter *) context;
    return record_deleter.delete_record(record);
}

RC Table::delete_record(Trx *trx, ConditionFilter *filter, int *deleted_count) {
    RecordDeleter deleter(*this, trx);
    RC rc = scan_record(trx, filter, -1, &deleter, record_reader_delete_adapter);
    if (deleted_count != nullptr) {
        *deleted_count = deleter.deleted_count();
    }
    return rc;
/*
    RecordDeleter deleter(*this, trx);
    RC rc = scan_record(trx, filter, -1, &deleter, record_reader_delete_adapter);
    if (deleted_count != nullptr) {
        *deleted_count = deleter.deleted_count();
    }
    return rc;*/
}

RC Table::delete_record(Trx *trx, Record *record) {
    RC rc = RC::SUCCESS;
    if (trx != nullptr) {
        rc = trx->delete_record(this, record);
    } else {
        rc = delete_entry_of_indexes(record->data, record->rid, false);// 重复代码 refer to commit_delete
        if (rc != RC::SUCCESS) {
            LOG_ERROR("Failed to delete indexes of record (rid=%d.%d). rc=%d:%s",
                      record->rid.page_num, record->rid.slot_num, rc, strrc(rc));
        } else {
            rc = record_handler_->delete_record(&record->rid);
        }
    }
    return rc;
}

RC Table::commit_delete(Trx *trx, const RID &rid) {
    RC rc = RC::SUCCESS;
    Record record;
    rc = record_handler_->get_record(&rid, &record);
    if (rc != RC::SUCCESS) {
        return rc;
    }
    rc = delete_entry_of_indexes(record.data, record.rid, false);
    if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to delete indexes of record(rid=%d.%d). rc=%d:%s",
                  rid.page_num, rid.slot_num, rc, strrc(rc));// panic?
    }

    rc = record_handler_->delete_record(&rid);
    if (rc != RC::SUCCESS) {
        return rc;
    }

    return rc;
}

RC Table::rollback_delete(Trx *trx, const RID &rid) {
    RC rc = RC::SUCCESS;
    Record record;
    rc = record_handler_->get_record(&rid, &record);
    if (rc != RC::SUCCESS) {
        return rc;
    }

    return trx->rollback_delete(this, record); // update record in place
}

RC Table::insert_entry_of_indexes(const char *record, const RID &rid) {
    RC rc = RC::SUCCESS;
    for (Index *index: indexes_) {
        rc = index->insert_entry(record, &rid);
        if (rc != RC::SUCCESS) {
            break;
        }
    }
    return rc;
}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists) {
    RC rc = RC::SUCCESS;
    for (Index *index: indexes_) {
        rc = index->delete_entry(record, &rid);
        if (rc != RC::SUCCESS) {
            if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
                break;
            }
        }
    }
    return rc;
}

Index *Table::find_index(const char *index_name) const {
    for (Index *index: indexes_) {
        if (0 == strcmp(index->index_meta().name(), index_name)) {
            return index;
        }
    }
    return nullptr;
}

IndexScanner *Table::find_index_for_scan(const DefaultConditionFilter &filter) {
    const ConDesc *field_cond_desc = nullptr;
    const ConDesc *value_cond_desc = nullptr;
    if (filter.left().is_attr && !filter.right().is_attr) {
        field_cond_desc = &filter.left();
        value_cond_desc = &filter.right();
    } else if (filter.right().is_attr && !filter.left().is_attr) {
        field_cond_desc = &filter.right();
        value_cond_desc = &filter.left();
    }
    if (field_cond_desc == nullptr || value_cond_desc == nullptr) {
        return nullptr;
    }

    const FieldMeta *field_meta = table_meta_.find_field_by_offset(field_cond_desc->attr_offset);
    if (nullptr == field_meta) {
        LOG_PANIC("Cannot find field by offset %d. table=%s",
                  field_cond_desc->attr_offset, name());
        return nullptr;
    }

    const IndexMeta *index_meta = table_meta_.find_index_by_field(field_meta->name());
    if (nullptr == index_meta) {
        return nullptr;
    }

    Index *index = find_index(index_meta->name());
    if (nullptr == index) {
        return nullptr;
    }

    return index->create_scanner(filter.comp_op(), (const char *) value_cond_desc->value);
}

IndexScanner *Table::find_index_for_scan(const ConditionFilter *filter) {
    if (nullptr == filter) {
        return nullptr;
    }

    // remove dynamic_cast
    const DefaultConditionFilter *default_condition_filter = dynamic_cast<const DefaultConditionFilter *>(filter);
    if (default_condition_filter != nullptr) {
        return find_index_for_scan(*default_condition_filter);
    }

    const CompositeConditionFilter *composite_condition_filter = dynamic_cast<const CompositeConditionFilter *>(filter);
    if (composite_condition_filter != nullptr) {
        int filter_num = composite_condition_filter->filter_num();
        for (int i = 0; i < filter_num; i++) {
            IndexScanner *scanner = find_index_for_scan(&composite_condition_filter->filter(i));
            if (scanner != nullptr) {
                return scanner; // 可以找到一个最优的，比如比较符号是=
            }
        }
    }
    return nullptr;
}

RC Table::sync() {
    RC rc = data_buffer_pool_->flush_all_pages(file_id_);
    if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to flush table's data pages. table=%s, rc=%d:%s", name(), rc, strrc(rc));
        return rc;
    }

    for (Index *index: indexes_) {
        rc = index->sync();
        if (rc != RC::SUCCESS) {
            LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
                      name(), index->index_meta().name(), rc, strrc(rc));
            return rc;
        }
    }
    LOG_INFO("Sync table over. table=%s", name());
    return rc;
}

bool Table::insert_unique_conflict(const char *record) {
    for (const auto index: indexes_) {
        if (index->index_meta().unique()) {
            std::string key;
            for (auto &field_meta : index->field_meta()) {
                std::string tmp(record + field_meta.offset(), field_meta.len());
                key += tmp;
            }
            if (index->unique_conflict(key)) {
                return true;
            }
        }
    }
    return false;
}
