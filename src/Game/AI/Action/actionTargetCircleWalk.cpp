#include "Game/AI/Action/actionTargetCircleWalk.h"

namespace uking::action {

TargetCircleWalk::TargetCircleWalk(const InitArg& arg) : TargetCircle(arg) {}

bool TargetCircleWalk::init_(sead::Heap* heap) {
    return TargetCircle::init_(heap);
}

void TargetCircleWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetCircle::enter_(params);
}

void TargetCircleWalk::leave_() {
    TargetCircle::leave_();
}

void TargetCircleWalk::loadParams_() {
    TargetCircle::loadParams_();
}

void TargetCircleWalk::calc_() {
    TargetCircle::calc_();
}

}  // namespace uking::action
