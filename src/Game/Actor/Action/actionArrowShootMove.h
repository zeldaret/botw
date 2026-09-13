#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ArrowShootMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ArrowShootMove, ksys::act::ai::Action)
public:
    explicit ArrowShootMove(const InitArg& arg);
    ~ArrowShootMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mIsShootByPlayer_d{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mFirstSpeed_d{};
    // dynamic_param at offset 0x30
    float* mAccel_d{};
    // dynamic_param at offset 0x38
    float* mAimSpeed_d{};
    // dynamic_param at offset 0x40
    float* mFallAccel_d{};
    // dynamic_param at offset 0x48
    float* mFallAimSpeed_d{};
    // dynamic_param at offset 0x50
    float* mGravity_d{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x60
    float* mAtPoint_d{};
    // dynamic_param at offset 0x68
    float* mAtRange_d{};
    // dynamic_param at offset 0x70
    float* mAtImpulse_d{};
    // dynamic_param at offset 0x78
    float* mAtImpact_d{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mRelativeVel_d{};
    // dynamic_param at offset 0x88
    int* mAtAttr_d{};
    // dynamic_param at offset 0x90
    int* mAtMinDamage_d{};
    // static_param at offset 0x98
    const float* mFallSpeedRatioByRange_s{};
};

}  // namespace uking::action
