#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCHorseResurrect : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCHorseResurrect, ksys::act::ai::Action)
public:
    explicit NPCHorseResurrect(const InitArg& arg);
    ~NPCHorseResurrect() override;

protected:
};

}  // namespace uking::action
