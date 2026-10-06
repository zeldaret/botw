#include "Game/Actor/Action/actionFollowIgniteToSelfPos.h"

namespace uking::action {

FollowIgniteToSelfPos::FollowIgniteToSelfPos(const InitArg& arg) : ASPlayRotateTurnToTarget(arg) {}

FollowIgniteToSelfPos::~FollowIgniteToSelfPos() = default;

bool FollowIgniteToSelfPos::init_(sead::Heap* heap) {
    return ASPlayRotateTurnToTarget::init_(heap);
}

void FollowIgniteToSelfPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ASPlayRotateTurnToTarget::enter_(params);
}

void FollowIgniteToSelfPos::leave_() {
    ASPlayRotateTurnToTarget::leave_();
}

void FollowIgniteToSelfPos::loadParams_() {
    ASPlayRotateTurnToTarget::loadParams_();
}

void FollowIgniteToSelfPos::calc_() {
    ASPlayRotateTurnToTarget::calc_();
}

}  // namespace uking::action
