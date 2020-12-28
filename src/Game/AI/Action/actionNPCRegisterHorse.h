#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCRegisterHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCRegisterHorse, ksys::act::ai::Action)
public:
    explicit NPCRegisterHorse(const InitArg& arg);
    ~NPCRegisterHorse() override;

protected:
};

}  // namespace uking::action
