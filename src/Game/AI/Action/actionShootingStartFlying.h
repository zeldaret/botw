#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ShootingStartFlying : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ShootingStartFlying, ksys::act::ai::Action)
public:
    explicit ShootingStartFlying(const InitArg& arg);
    ~ShootingStartFlying() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mInitialVelocityMax_s{};
    // static_param at offset 0x28
    const float* mInitialVelocityMin_s{};
    // static_param at offset 0x30
    const float* mInitialAngleRange_s{};
    // static_param at offset 0x38
    const float* mLookSuccessRate_s{};
    // static_param at offset 0x40
    const float* mMaxWaterDepth_s{};
    // static_param at offset 0x48
    const float* mGravity_s{};
};

}  // namespace uking::action
