#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCCalculateMaterialValue : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCCalculateMaterialValue, ksys::act::ai::Action)
public:
    explicit NPCCalculateMaterialValue(const InitArg& arg);
    ~NPCCalculateMaterialValue() override;

protected:
};

}  // namespace uking::action
