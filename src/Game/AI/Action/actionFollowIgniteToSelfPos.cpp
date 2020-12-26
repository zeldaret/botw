#include "Game/AI/Action/actionFollowIgniteToSelfPos.h"

namespace uking::action {

FollowIgniteToSelfPos::FollowIgniteToSelfPos(const InitArg& arg) : RotateTurnToTarget(arg) {}

FollowIgniteToSelfPos::~FollowIgniteToSelfPos() = default;

bool FollowIgniteToSelfPos::init_(sead::Heap* heap) {
    return RotateTurnToTarget::init_(heap);
}

void FollowIgniteToSelfPos::enter_(ksys::act::ai::InlineParamPack* params) {
    RotateTurnToTarget::enter_(params);
}

void FollowIgniteToSelfPos::leave_() {
    RotateTurnToTarget::leave_();
}

void FollowIgniteToSelfPos::loadParams_() {
    RotateTurnToTarget::loadParams_();
}

void FollowIgniteToSelfPos::calc_() {
    RotateTurnToTarget::calc_();
}

}  // namespace uking::action
