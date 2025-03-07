//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2025
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "td/telegram/PaidReactionType.h"

#include "td/utils/common.h"
#include "td/utils/tl_helpers.h"

namespace td {

template <class StorerT>
void PaidReactionType::store(StorerT &storer) const {
  bool has_dialog_id = dialog_id_.is_valid();
  BEGIN_STORE_FLAGS();
  STORE_FLAG(has_dialog_id);
  END_STORE_FLAGS();
  td::store(type_, storer);
  if (has_dialog_id) {
    td::store(dialog_id_, storer);
  }
}

template <class ParserT>
void PaidReactionType::parse(ParserT &parser) {
  bool has_dialog_id;
  BEGIN_PARSE_FLAGS();
  PARSE_FLAG(has_dialog_id);
  END_PARSE_FLAGS();
  td::parse(type_, parser);
  if (has_dialog_id) {
    td::parse(dialog_id_, parser);
  }
}

}  // namespace td
