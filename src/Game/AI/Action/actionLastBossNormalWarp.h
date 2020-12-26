#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LastBossNormalWarp : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LastBossNormalWarp, ksys::act::ai::Action)
public:
    explicit LastBossNormalWarp(const InitArg& arg);
    ~LastBossNormalWarp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mOffsetLength_s{};
    // static_param at offset 0x28
    const float* mOffsetY_s{};
    // static_param at offset 0x30
    const float* mWarpTime_s{};
    // static_param at offset 0x38
    const float* mCheckShapeRadius_s{};
    // static_param at offset 0x40
    const bool* mIsUseChangePos_s{};
    // static_param at offset 0x48
    const bool* mIsEscapeFromPlayer_s{};
    // static_param at offset 0x50
    const bool* mIsWarpAtGround_s{};
    // static_param at offset 0x58
    const bool* mIsChasePlayer_s{};
    // static_param at offset 0x60
    const bool* mDisableGroundHit_s{};
    // static_param at offset 0x68
    const bool* mDisableAirWallHit_s{};
    // static_param at offset 0x70
    const sead::Vector3f* mChaseDist_s{};
    // static_param at offset 0x78
    const sead::Vector3f* mChaseDistOffset_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mHomePosOffset_s{};
    // dynamic_param at offset 0x88
    bool* mIsReturnHome_d{};
    // dynamic_param at offset 0x90
    bool* mIsForceWarp_d{};
    // dynamic_param at offset 0x98
    bool* mIsPartsActorTgOn_d{};
    // dynamic_param at offset 0xa0
    bool* mIsKeepDisableDraw_d{};
    // dynamic_param at offset 0xa8
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
