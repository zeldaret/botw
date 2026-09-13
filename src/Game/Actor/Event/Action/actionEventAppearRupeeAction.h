#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventAppearRupeeAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventAppearRupeeAction, ksys::act::ai::Action)
public:
    explicit EventAppearRupeeAction(const InitArg& arg);

    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mIsVisible_d{};
};

}  // namespace uking::action
