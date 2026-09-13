#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventIncreaseFameAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventIncreaseFameAction, ksys::act::ai::Action)
public:
    explicit EventIncreaseFameAction(const InitArg& arg);

    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mValue_d{};
};

}  // namespace uking::action
