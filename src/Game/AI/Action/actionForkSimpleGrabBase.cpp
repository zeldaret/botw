#include "Game/AI/Action/actionForkSimpleGrabBase.h"

namespace uking::action {

ForkSimpleGrabBase::ForkSimpleGrabBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSimpleGrabBase::~ForkSimpleGrabBase() = default;

bool ForkSimpleGrabBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSimpleGrabBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkSimpleGrabBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkSimpleGrabBase::loadParams_() {
    getStaticParam(&mGrabIdx_s, "GrabIdx");
    getStaticParam(&mIsNoGrabSuccess_s, "IsNoGrabSuccess");
}

void ForkSimpleGrabBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
