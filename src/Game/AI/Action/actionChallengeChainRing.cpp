#include "Game/AI/Action/actionChallengeChainRing.h"

namespace uking::action {

ChallengeChainRing::ChallengeChainRing(const InitArg& arg) : FollowChallenge(arg) {}

ChallengeChainRing::~ChallengeChainRing() = default;

bool ChallengeChainRing::init_(sead::Heap* heap) {
    return FollowChallenge::init_(heap);
}

void ChallengeChainRing::enter_(ksys::act::ai::InlineParamPack* params) {
    FollowChallenge::enter_(params);
}

void ChallengeChainRing::leave_() {
    FollowChallenge::leave_();
}

void ChallengeChainRing::loadParams_() {
    FollowChallenge::loadParams_();
    getMapUnitParam(&mChainRingOrbitSpeed_m, "ChainRingOrbitSpeed");
    getMapUnitParam(&mIsFirstNode_m, "IsFirstNode");
}

void ChallengeChainRing::calc_() {
    FollowChallenge::calc_();
}

}  // namespace uking::action
