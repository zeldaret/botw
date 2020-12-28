#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCEndHorseReception : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCEndHorseReception, ksys::act::ai::Action)
public:
    explicit NPCEndHorseReception(const InitArg& arg);
    ~NPCEndHorseReception() override;

protected:
};

}  // namespace uking::action
