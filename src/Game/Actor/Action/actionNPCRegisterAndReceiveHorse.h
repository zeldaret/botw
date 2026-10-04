#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCRegisterAndReceiveHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCRegisterAndReceiveHorse, ksys::act::ai::Action)
public:
    explicit NPCRegisterAndReceiveHorse(const InitArg& arg);
    ~NPCRegisterAndReceiveHorse() override;

protected:
};

}  // namespace uking::action
