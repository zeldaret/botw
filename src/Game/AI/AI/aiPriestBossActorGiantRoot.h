#pragma once

#include "Game/AI/AI/aiPriestBossActorRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossActorGiantRoot : public PriestBossActorRoot {
    SEAD_RTTI_OVERRIDE(PriestBossActorGiantRoot, PriestBossActorRoot)
public:
    explicit PriestBossActorGiantRoot(const InitArg& arg);
    ~PriestBossActorGiantRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const float* mFreqIronBallAttack_s{};
    // static_param at offset 0x48
    const float* mFreqBigEarthReleaseAttack_s{};
    // static_param at offset 0x50
    const float* mFreqEyeBeamAttack_s{};
    // static_param at offset 0x58
    const float* mFreqStageRotation_s{};
    // static_param at offset 0x60
    const float* mFloatDistFromPlayer_s{};
    // static_param at offset 0x68
    const bool* mIsFreeMoving_s{};
    // aitree_variable at offset 0x70
    float* mKeepDistFromGround_a{};
    // aitree_variable at offset 0x78
    bool* mIsActive_a{};
    // aitree_variable at offset 0x80
    bool* mIsArrivedAtDestination_a{};
    // aitree_variable at offset 0x88
    sead::Vector3f* mDestinationPos_a{};
    // aitree_variable at offset 0x90
    sead::Vector3f* mFacePos_a{};
};

}  // namespace uking::ai
