#pragma once

#include "Game/AI/AI/aiEnemyRangeKeepMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BreathEnemyRangeKeepMove : public EnemyRangeKeepMove {
    SEAD_RTTI_OVERRIDE(BreathEnemyRangeKeepMove, EnemyRangeKeepMove)
public:
    explicit BreathEnemyRangeKeepMove(const InitArg& arg);
    ~BreathEnemyRangeKeepMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x110
    const int* mEnlargeTime_s{};
    // static_param at offset 0x118
    const float* mAttackRatio_s{};
    // static_param at offset 0x120
    const float* mBreathSize_s{};
    // static_param at offset 0x128
    sead::SafeString mBreathName_s{};
    // static_param at offset 0x138
    sead::SafeString mBaseNode_s{};
    // static_param at offset 0x148
    const int* mLoopTime_s{};
    // static_param at offset 0x150
    const float* mBreathEndDist_s{};
    // static_param at offset 0x158
    const int* mBreathMinTime_s{};
};

}  // namespace uking::ai
