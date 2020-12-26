#include "Game/AI/Action/actionFollowChallenge.h"

namespace uking::action {

FollowChallenge::FollowChallenge(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FollowChallenge::~FollowChallenge() = default;

bool FollowChallenge::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FollowChallenge::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FollowChallenge::leave_() {
    ksys::act::ai::Action::leave_();
}

void FollowChallenge::loadParams_() {
    getMapUnitParam(&mGimmickTimeLimit_m, "GimmickTimeLimit");
    getMapUnitParam(&mIsBillboard_m, "IsBillboard");
}

void FollowChallenge::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
