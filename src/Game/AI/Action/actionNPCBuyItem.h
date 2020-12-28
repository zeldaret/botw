#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCBuyItem : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCBuyItem, ksys::act::ai::Action)
public:
    explicit NPCBuyItem(const InitArg& arg);
    ~NPCBuyItem() override;

protected:
};

}  // namespace uking::action
