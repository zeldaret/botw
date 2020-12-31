#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossIronBall : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossIronBall, ksys::act::ai::Ai)
public:
    explicit PriestBossIronBall(const InitArg& arg);
    ~PriestBossIronBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mIronBallWaitThunderTime_s{};
    // static_param at offset 0x40
    const int* mChangeEndAnime_s{};
    // static_param at offset 0x48
    const float* mIronBallOffsetY_s{};
    // static_param at offset 0x50
    const float* mIronBallRadius_s{};
    // static_param at offset 0x58
    const float* mIronBallAngle_s{};
    // static_param at offset 0x60
    const float* mIronBallAngleOffset_s{};
    // static_param at offset 0x68
    const bool* mIsAfterAttack_s{};
    // static_param at offset 0x70
    sead::SafeString mIronSummonLeftBoneName_s{};
    // static_param at offset 0x80
    sead::SafeString mIronSummonRightBoneName_s{};
    // aitree_variable at offset 0x90
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai
