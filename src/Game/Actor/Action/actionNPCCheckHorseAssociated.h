#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCCheckHorseAssociated : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCCheckHorseAssociated, ksys::act::ai::Action)
public:
    explicit NPCCheckHorseAssociated(const InitArg& arg);
    ~NPCCheckHorseAssociated() override;

protected:
};

}  // namespace uking::action
