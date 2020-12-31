#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LastBossBeamAttackRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LastBossBeamAttackRoot, ksys::act::ai::Ai)
public:
    explicit LastBossBeamAttackRoot(const InitArg& arg);
    ~LastBossBeamAttackRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mAttackPowerForPlayer_s{};
    // static_param at offset 0x40
    const int* mAttackPower_s{};
    // static_param at offset 0x48
    const int* mAtMinDamage_s{};
    // static_param at offset 0x50
    const int* mAddAttackPower_s{};
    // static_param at offset 0x58
    const float* mWaitTime_s{};
    // static_param at offset 0x60
    const float* mKeepDistance_s{};
    // static_param at offset 0x68
    const float* mMoveSpeed_s{};
    // static_param at offset 0x70
    const float* mInitSpeed_s{};
    // static_param at offset 0x78
    const float* mAccel_s{};
    // static_param at offset 0x80
    const float* mKeepDistanceRand_s{};
    // static_param at offset 0x88
    const float* mRandKeepFrame_s{};
    // static_param at offset 0x90
    const float* mBrakeStartFrame_s{};
    // static_param at offset 0x98
    const float* mMoveYSpeed_s{};
    // static_param at offset 0xa0
    const bool* mIsMove_s{};
    // static_param at offset 0xa8
    const bool* mIsChangeable_s{};
    // static_param at offset 0xb0
    const bool* mIsCreateGuardEffect_s{};
    // static_param at offset 0xb8
    const sead::Vector3f* mReflectOffset_s{};
};

}  // namespace uking::ai
