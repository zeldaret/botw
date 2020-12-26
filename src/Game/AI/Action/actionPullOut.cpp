#include "Game/AI/Action/actionPullOut.h"

namespace uking::action {

PullOut::PullOut(const InitArg& arg) : ActionWithAS(arg) {}

PullOut::~PullOut() = default;

bool PullOut::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void PullOut::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void PullOut::leave_() {
    ActionWithAS::leave_();
}

void PullOut::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mAnimGrabPos_s, "AnimGrabPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void PullOut::calc_() {
    ActionWithAS::calc_();
}

}  // namespace uking::action
