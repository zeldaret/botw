#include "Game/Actor/Action/actionChallengeChainRing.h"

namespace uking::action {

ChallengeChainRing::ChallengeChainRing(const InitArg& arg) : AppearFollowChallenge(arg) {}

ChallengeChainRing::~ChallengeChainRing() = default;

bool ChallengeChainRing::init_(sead::Heap* heap) {
    return AppearFollowChallenge::init_(heap);
}

void ChallengeChainRing::enter_(ksys::act::ai::InlineParamPack* params) {
    AppearFollowChallenge::enter_(params);
}

void ChallengeChainRing::leave_() {
    AppearFollowChallenge::leave_();
}

void ChallengeChainRing::loadParams_() {
    AppearFollowChallenge::loadParams_();
    getMapUnitParam(&mChainRingOrbitSpeed_m, "ChainRingOrbitSpeed");
    getMapUnitParam(&mIsFirstNode_m, "IsFirstNode");
}

void ChallengeChainRing::calc_() {
    AppearFollowChallenge::calc_();
}

}  // namespace uking::action
