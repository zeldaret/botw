#pragma once

#include "Game/AI/AI/aiDomesticNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DogNormal : public DomesticNormal {
    SEAD_RTTI_OVERRIDE(DogNormal, DomesticNormal)
public:
    explicit DogNormal(const InitArg& arg);
    ~DogNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x3a0
    const int* mNumFriendlyFoodForLeadTreasure_s{};
    // static_param at offset 0x3a8
    const float* mMaxFollowDist_s{};
    // static_param at offset 0x3b0
    const float* mMaxFollowFriendDecayRate_s{};
    // static_param at offset 0x3b8
    const float* mFoodFriendRate_s{};
    // static_param at offset 0x3c0
    const float* mFoodFriendDist_s{};
    // static_param at offset 0x3c8
    const float* mNearFriendRate_s{};
    // static_param at offset 0x3d0
    const float* mNearFriendDist_s{};
    // static_param at offset 0x3d8
    const float* mFarFriendDecayRate_s{};
    // static_param at offset 0x3e0
    const float* mFarFriendDist_s{};
    // static_param at offset 0x3e8
    const float* mFarFriendFriendlyDist_s{};
    // static_param at offset 0x3f0
    const float* mAttackFriendDecayRate_s{};
    // static_param at offset 0x3f8
    const float* mFriendTickRate_s{};
    // static_param at offset 0x400
    const float* mNoMoveFriendDecayRate_s{};
    // static_param at offset 0x408
    const float* mNoMoveThreshold_s{};
    // static_param at offset 0x410
    const float* mFramesKeepMaxFriendly_s{};
    // static_param at offset 0x418
    const float* mFramesStayAfterLead_s{};
    // static_param at offset 0x420
    const float* mAngleTurnToPlayer_s{};
};

}  // namespace uking::ai
