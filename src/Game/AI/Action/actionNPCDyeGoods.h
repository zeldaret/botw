#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCDyeGoods : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCDyeGoods, ksys::act::ai::Action)
public:
    explicit NPCDyeGoods(const InitArg& arg);
    ~NPCDyeGoods() override;

protected:
};

}  // namespace uking::action
