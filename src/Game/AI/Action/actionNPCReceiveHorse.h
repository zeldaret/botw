#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCReceiveHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCReceiveHorse, ksys::act::ai::Action)
public:
    explicit NPCReceiveHorse(const InitArg& arg);
    ~NPCReceiveHorse() override;

protected:
};

}  // namespace uking::action
