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
// Created by wangyunlai.wyl on 2021/5/19.
//

#include "storage/common/index.h"
#include <vector>

RC Index::init(const IndexMeta &index_meta, std::vector<const FieldMeta*> &fields_meta) {
  index_meta_ = index_meta;
  for (auto& field_meta : fields_meta)
    fields_meta_.push_back(*field_meta);
  return RC::SUCCESS;
}

RC Index::init(const IndexMeta &index_meta, const FieldMeta &field_meta) {
  index_meta_ = index_meta;
  fields_meta_.push_back(field_meta);
  return RC::SUCCESS;
}
