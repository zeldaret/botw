#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCReleaseHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCReleaseHorse, ksys::act::ai::Action)
public:
    explicit NPCReleaseHorse(const InitArg& arg);
    ~NPCReleaseHorse() override;

protected:
};

}  // namespace uking::action
