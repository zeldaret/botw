#include "Game/AI/Action/actionForkSimpleGrab.h"

namespace uking::action {

ForkSimpleGrab::ForkSimpleGrab(const InitArg& arg) : ForkSimpleGrabBase(arg) {}

ForkSimpleGrab::~ForkSimpleGrab() = default;

bool ForkSimpleGrab::init_(sead::Heap* heap) {
    return ForkSimpleGrabBase::init_(heap);
}

void ForkSimpleGrab::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkSimpleGrabBase::enter_(params);
}

void ForkSimpleGrab::leave_() {
    ForkSimpleGrabBase::leave_();
}

void ForkSimpleGrab::loadParams_() {
    ForkSimpleGrabBase::loadParams_();
    getStaticParam(&mCheckRadius_s, "CheckRadius");
}

void ForkSimpleGrab::calc_() {
    ForkSimpleGrabBase::calc_();
}

}  // namespace uking::action
