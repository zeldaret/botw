#pragma once

#include "Game/AI/AI/aiPriestBossIronBall.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossIronBallStageRotate : public PriestBossIronBall {
    SEAD_RTTI_OVERRIDE(PriestBossIronBallStageRotate, PriestBossIronBall)
public:
    explicit PriestBossIronBallStageRotate(const InitArg& arg);
    ~PriestBossIronBallStageRotate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x6c0
    const float* mIronBallSummonRadius_s{};
    // static_param at offset 0x6c8
    const float* mIronBallSummonArchAngle_s{};
    // static_param at offset 0x6d0
    const float* mIronBallSummonOffsetY_s{};
    // aitree_variable at offset 0x6d8
    bool* mIsActive_a{};
    // aitree_variable at offset 0x6e0
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai
