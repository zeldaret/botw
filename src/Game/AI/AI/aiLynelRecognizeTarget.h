#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelRecognizeTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelRecognizeTarget, ksys::act::ai::Ai)
public:
    explicit LynelRecognizeTarget(const InitArg& arg);
    ~LynelRecognizeTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mAttensionStartPoint_s{};
    // static_param at offset 0x40
    const int* mObserveEndPoint_s{};
    // static_param at offset 0x48
    const int* mDrawnWeaponPoint_s{};
    // static_param at offset 0x50
    const int* mWeaponAimPoint_s{};
    // static_param at offset 0x58
    const int* mAttackPoint_s{};
    // static_param at offset 0x60
    const int* mDashPoint_s{};
    // static_param at offset 0x68
    const int* mAppPoint_s{};
    // static_param at offset 0x70
    const int* mHorseRidePoint_s{};
    // static_param at offset 0x78
    const int* mDamagePoint_s{};
    // static_param at offset 0x80
    const int* mTrickedMaskPoint_s{};
    // static_param at offset 0x88
    const int* mBombPoint_s{};
    // static_param at offset 0x90
    const int* mAimPoint_s{};
    // static_param at offset 0x98
    const int* mNearDistPoint_s{};
    // static_param at offset 0xa0
    const int* mMiddleDistPoint_s{};
    // static_param at offset 0xa8
    const int* mTiredTime_s{};
    // static_param at offset 0xb0
    const int* mTiredPoint_s{};
    // static_param at offset 0xb8
    const int* mForceBattleStartTime_s{};
    // static_param at offset 0xc0
    const float* mNearDistance_s{};
    // static_param at offset 0xc8
    const float* mFarDistance_s{};
    // static_param at offset 0xd0
    const float* mAimAngle_s{};
    // map_unit_param at offset 0xd8
    const bool* mIsNearCreate_m{};
    // aitree_variable at offset 0xe0
    int* mLynelAIFlags_a{};
    // aitree_variable at offset 0xe8
    int* mLynelAreaAlarmPoint_a{};
};

}  // namespace uking::ai
