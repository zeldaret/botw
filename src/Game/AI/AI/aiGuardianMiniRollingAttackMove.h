#pragma once

#include "Game/AI/AI/aiEnemyRangeKeepMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniRollingAttackMove : public EnemyRangeKeepMove {
    SEAD_RTTI_OVERRIDE(GuardianMiniRollingAttackMove, EnemyRangeKeepMove)
public:
    explicit GuardianMiniRollingAttackMove(const InitArg& arg);
    ~GuardianMiniRollingAttackMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x110
    sead::SafeString mRootNodeName_s{};
    // static_param at offset 0x120
    sead::SafeString mAttackNodeName_s{};
    // static_param at offset 0x130
    sead::SafeString mAttackASName_s{};
    // static_param at offset 0x140
    const int* mRollingNumMin_s{};
    // static_param at offset 0x148
    const int* mRollingNumMax_s{};
    // static_param at offset 0x150
    const int* mRollingWaitTime_s{};
    // static_param at offset 0x158
    const int* mRollingIntervalTime_s{};
    // static_param at offset 0x160
    const int* mStopRollingNum_s{};
    // static_param at offset 0x168
    const float* mJustAvoidSideDist_s{};
    // static_param at offset 0x170
    const float* mJustAvoidBackDist_s{};
    // static_param at offset 0x178
    const float* mJustAvoidAngle_s{};
    // static_param at offset 0x180
    const float* mRotSpeed_s{};
    // static_param at offset 0x188
    const float* mBackWalkRotSpeedRatio_s{};
    // static_param at offset 0x190
    const float* mRushRotSpeedRatio_s{};
    // static_param at offset 0x198
    const int* mAttackType_s{};
    // static_param at offset 0x1a0
    const int* mBackWalkMinTime_s{};
    // static_param at offset 0x1a8
    const int* mBackWalkRollingStartTime_s{};
    // static_param at offset 0x1b0
    const float* mBackWalkDist_s{};
    // static_param at offset 0x1b8
    const int* mRushAttackImpulse_s{};
    // static_param at offset 0x1c0
    const int* mRollingStopTime_s{};
    // static_param at offset 0x1c8
    const bool* mIsValidChanceTime_s{};
    // static_param at offset 0x1d0
    const int* mCrashDamage_s{};
    // static_param at offset 0x1d8
    const int* mBreakPillarTime_s{};
};

}  // namespace uking::ai
