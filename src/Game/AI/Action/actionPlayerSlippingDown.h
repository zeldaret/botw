#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerSlippingDown : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PlayerSlippingDown, ksys::act::ai::Action)
public:
    explicit PlayerSlippingDown(const InitArg& arg);
    ~PlayerSlippingDown() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mDamageInterval_s{};
    // static_param at offset 0x28
    const int* mDamageVal_s{};
    // static_param at offset 0x30
    const float* mChangeableInterval_s{};
    // static_param at offset 0x38
    const float* mChangeableIntervalInAir_s{};
    // static_param at offset 0x40
    const float* mEnableSpeedDamage_s{};
    // dynamic_param at offset 0x48
    float* mInitAddLinearImpulse_d{};
    // dynamic_param at offset 0x50
    float* mInitAddRollImpulse_d{};
    // dynamic_param at offset 0x58
    bool* mIsAddImpulse_d{};
};

}  // namespace uking::action
