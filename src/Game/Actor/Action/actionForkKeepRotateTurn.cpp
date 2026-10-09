#include "Game/Actor/Action/actionForkKeepRotateTurn.h"

namespace uking::action {

ForkKeepRotateTurn::ForkKeepRotateTurn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkKeepRotateTurn::~ForkKeepRotateTurn() = default;

bool ForkKeepRotateTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkKeepRotateTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkKeepRotateTurn::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkKeepRotateTurn::loadParams_() {
    getStaticParam(&mMinRotSpd_s, "MinRotSpd");
    getStaticParam(&mEndAngle_s, "EndAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkKeepRotateTurn::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
