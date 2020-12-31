#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DashAndAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DashAndAttack, ksys::act::ai::Ai)
public:
    explicit DashAndAttack(const InitArg& arg);
    ~DashAndAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const int* mAttackFrame_s{};
    // static_param at offset 0x48
    const float* mOffsetLR_s{};
    // static_param at offset 0x50
    const float* mAttackRange_s{};
    // static_param at offset 0x58
    const float* mTiredAngle_s{};
    // static_param at offset 0x60
    const float* mTargetSpeedClampMax_s{};
    // static_param at offset 0x68
    const bool* mIsAbleSkipNear_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetVel_d{};
};

}  // namespace uking::ai
