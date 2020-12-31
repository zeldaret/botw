#pragma once

#include "Game/AI/AI/aiPriestBossMode.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossGiantStageRotRoot : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossGiantStageRotRoot, PriestBossMode)
public:
    explicit PriestBossGiantStageRotRoot(const InitArg& arg);
    ~PriestBossGiantStageRotRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const float* mCentralAngle_s{};
    // static_param at offset 0x48
    const float* mPercentRadiusHeight_s{};
    // static_param at offset 0x50
    const float* mIronBallHeightOffset_s{};
    // static_param at offset 0x58
    const float* mArcPercent_s{};
    // static_param at offset 0x60
    const float* mZOffset_s{};
    // static_param at offset 0x68
    const float* mZOffsetIndex_s{};
    // static_param at offset 0x70
    const float* mHoldBallsCounterLength_s{};
    // static_param at offset 0x78
    const float* mBallsReleaseIntervalFrames_s{};
    // aitree_variable at offset 0x80
    float* mKeepDistFromGround_a{};
    // aitree_variable at offset 0x88
    bool* mIsActive_a{};
    // aitree_variable at offset 0x90
    sead::Vector3f* mFacePos_a{};
    // aitree_variable at offset 0x98
    sead::Vector3f* mDestinationPos_a{};
    // aitree_variable at offset 0xa0
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai
