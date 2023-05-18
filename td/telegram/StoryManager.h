//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2023
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "td/telegram/DialogId.h"
#include "td/telegram/MessageEntity.h"
#include "td/telegram/StoryId.h"
#include "td/telegram/StoryInteractionInfo.h"
#include "td/telegram/UserId.h"
#include "td/telegram/UserPrivacySettingRule.h"

#include "td/actor/actor.h"

#include "td/utils/common.h"
#include "td/utils/WaitFreeHashMap.h"

namespace td {

class StoryContent;
class Td;

class StoryManager final : public Actor {
 public:
  StoryManager(Td *td, ActorShared<> parent);
  StoryManager(const StoryManager &) = delete;
  StoryManager &operator=(const StoryManager &) = delete;
  StoryManager(StoryManager &&) = delete;
  StoryManager &operator=(StoryManager &&) = delete;
  ~StoryManager() final;

  StoryId on_get_story(DialogId owner_dialog_id, telegram_api::object_ptr<telegram_api::storyItem> &&story_item);

 private:
  struct Story {
    int32 date_ = 0;
    int32 expire_date_ = 0;
    bool is_pinned_ = false;
    bool is_public_ = false;
    bool is_for_close_friends_ = false;
    StoryInteractionInfo interaction_info_;
    UserPrivacySettingRules privacy_rules_;
    unique_ptr<StoryContent> content_;
    FormattedText caption_;
  };

  void tear_down() final;

  const Story *get_story(StoryId story_id) const;

  Story *get_story_editable(StoryId story_id);

  static bool is_local_story_id(StoryId story_id);

  WaitFreeHashMap<StoryId, unique_ptr<Story>, StoryIdHash> stories_;

  Td *td_;
  ActorShared<> parent_;
};

}  // namespace td