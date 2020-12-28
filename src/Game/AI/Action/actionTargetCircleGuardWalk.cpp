#include "Game/AI/Action/actionTargetCircleGuardWalk.h"

namespace uking::action {

TargetCircleGuardWalk::TargetCircleGuardWalk(const InitArg& arg) : TargetCircle(arg) {}

bool TargetCircleGuardWalk::init_(sead::Heap* heap) {
    return TargetCircle::init_(heap);
}

void TargetCircleGuardWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetCircle::enter_(params);
}

void TargetCircleGuardWalk::leave_() {
    TargetCircle::leave_();
}

void TargetCircleGuardWalk::loadParams_() {
    TargetCircle::loadParams_();
}

void TargetCircleGuardWalk::calc_() {
    TargetCircle::calc_();
}

}  // namespace uking::action
