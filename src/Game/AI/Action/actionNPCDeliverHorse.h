#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCDeliverHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCDeliverHorse, ksys::act::ai::Action)
public:
    explicit NPCDeliverHorse(const InitArg& arg);
    ~NPCDeliverHorse() override;

protected:
};

}  // namespace uking::action
