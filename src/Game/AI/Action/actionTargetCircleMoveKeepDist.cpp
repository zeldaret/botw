#include "Game/AI/Action/actionTargetCircleMoveKeepDist.h"

namespace uking::action {

TargetCircleMoveKeepDist::TargetCircleMoveKeepDist(const InitArg& arg) : TargetCircle(arg) {}

TargetCircleMoveKeepDist::~TargetCircleMoveKeepDist() = default;

bool TargetCircleMoveKeepDist::init_(sead::Heap* heap) {
    return TargetCircle::init_(heap);
}

void TargetCircleMoveKeepDist::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetCircle::enter_(params);
}

void TargetCircleMoveKeepDist::leave_() {
    TargetCircle::leave_();
}

void TargetCircleMoveKeepDist::loadParams_() {
    TargetCircle::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void TargetCircleMoveKeepDist::calc_() {
    TargetCircle::calc_();
}

}  // namespace uking::action
