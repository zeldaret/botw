#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AppearMagneForce : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AppearMagneForce, ksys::act::ai::Action)
public:
    explicit AppearMagneForce(const InitArg& arg);
    ~AppearMagneForce() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMaxMagneForceRange_s{};
    // static_param at offset 0x28
    const float* mMinMagneForceRange_s{};
    // static_param at offset 0x30
    const float* mMagneControlSpeed_s{};
    // static_param at offset 0x38
    const float* mMagneForceRadius_s{};
    // static_param at offset 0x40
    const float* mMagneForceDamp_s{};
    // static_param at offset 0x48
    const float* mMagneForceVelRate_s{};
    // static_param at offset 0x50
    const float* mObjectTerror_s{};
    // static_param at offset 0x58
    const float* mMagneShootSpeed_s{};
    // static_param at offset 0x60
    const float* mMagneControlRotateSpeed_s{};
    // static_param at offset 0x68
    const float* mMagneControlUpDownSpeed_s{};
    // static_param at offset 0x70
    const float* mResistanceSpeedScale_s{};
    // static_param at offset 0x78
    const float* mMaxMagneHeight_s{};
    // static_param at offset 0x80
    const float* mCancelAngle_s{};
    // static_param at offset 0x88
    const float* mCancelHeight_s{};
    // static_param at offset 0x90
    const float* mCancelAngleFixed_s{};
    // static_param at offset 0x98
    const float* mCancelHeightFixed_s{};
    // static_param at offset 0xa0
    const float* mGyroUpDownSpeed_s{};
    // static_param at offset 0xa8
    const float* mGyroRotateSpeed_s{};
};

}  // namespace uking::action
