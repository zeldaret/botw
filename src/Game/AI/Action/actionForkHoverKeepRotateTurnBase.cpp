#include "Game/AI/Action/actionForkHoverKeepRotateTurnBase.h"

namespace uking::action {

ForkHoverKeepRotateTurnBase::ForkHoverKeepRotateTurnBase(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkHoverKeepRotateTurnBase::~ForkHoverKeepRotateTurnBase() = default;

bool ForkHoverKeepRotateTurnBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkHoverKeepRotateTurnBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkHoverKeepRotateTurnBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkHoverKeepRotateTurnBase::loadParams_() {
    getStaticParam(&mMinRotSpd_s, "MinRotSpd");
    getStaticParam(&mEndAngle_s, "EndAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkHoverKeepRotateTurnBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
