#include "Game/Actor/Action/actionForkSimpleGrab.h"

namespace uking::action {

ForkSimpleGrab::ForkSimpleGrab(const InitArg& arg) : ForkGrabBase(arg) {}

ForkSimpleGrab::~ForkSimpleGrab() = default;

bool ForkSimpleGrab::init_(sead::Heap* heap) {
    return ForkGrabBase::init_(heap);
}

void ForkSimpleGrab::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkGrabBase::enter_(params);
}

void ForkSimpleGrab::leave_() {
    ForkGrabBase::leave_();
}

void ForkSimpleGrab::loadParams_() {
    ForkGrabBase::loadParams_();
    getStaticParam(&mCheckRadius_s, "CheckRadius");
}

void ForkSimpleGrab::calc_() {
    ForkGrabBase::calc_();
}

}  // namespace uking::action
