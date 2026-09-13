#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkFixedAngleVacuumShootTarget : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkFixedAngleVacuumShootTarget, ksys::act::ai::Action)
public:
    explicit ForkFixedAngleVacuumShootTarget(const InitArg& arg);
    ~ForkFixedAngleVacuumShootTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mShootSpeedMin_s{};
    // static_param at offset 0x28
    const float* mShootSpeedMax_s{};
    // static_param at offset 0x30
    const float* mAngle_s{};
    // static_param at offset 0x38
    const float* mMaxNoiseDist_s{};
    // static_param at offset 0x40
    const float* mOffsetHeight_s{};
    // static_param at offset 0x48
    const bool* mIsReuseBullet_s{};
    // static_param at offset 0x50
    sead::SafeString mBaseNode_s{};
    // static_param at offset 0x60
    sead::SafeString mPartsKey_s{};
    // static_param at offset 0x70
    const sead::Vector3f* mShootOffset_s{};
    // static_param at offset 0x78
    const sead::Vector3f* mShootRotate_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mShootRotSpeed_s{};
    // dynamic_param at offset 0x88
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
