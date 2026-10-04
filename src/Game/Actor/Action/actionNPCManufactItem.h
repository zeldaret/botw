#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCManufactItem : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCManufactItem, ksys::act::ai::Action)
public:
    explicit NPCManufactItem(const InitArg& arg);
    ~NPCManufactItem() override;

protected:
};

}  // namespace uking::action
