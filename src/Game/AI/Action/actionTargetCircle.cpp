#include "Game/AI/Action/actionTargetCircle.h"

namespace uking::action {

TargetCircle::TargetCircle(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TargetCircle::~TargetCircle() = default;

bool TargetCircle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TargetCircle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TargetCircle::leave_() {
    ksys::act::ai::Action::leave_();
}

void TargetCircle::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mRotDist_s, "RotDist");
    getDynamicParam(&mRotDir_d, "RotDir");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void TargetCircle::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
