#pragma once

#include "Game/AI/Action/actionFollowChallenge.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChallengeChainRing : public FollowChallenge {
    SEAD_RTTI_OVERRIDE(ChallengeChainRing, FollowChallenge)
public:
    explicit ChallengeChainRing(const InitArg& arg);
    ~ChallengeChainRing() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0xab0
    const float* mChainRingOrbitSpeed_m{};
    // map_unit_param at offset 0xab8
    const bool* mIsFirstNode_m{};
};

}  // namespace uking::action
