#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetDispStaminaGauge : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetDispStaminaGauge, ksys::act::ai::Action)
public:
    explicit SetDispStaminaGauge(const InitArg& arg);
    ~SetDispStaminaGauge() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    bool* mIsDisplay_d{};
    // dynamic_param at offset 0x28
    bool* mIsDisplayEx_d{};
};

}  // namespace uking::action
