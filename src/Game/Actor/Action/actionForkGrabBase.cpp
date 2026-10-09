#include "Game/Actor/Action/actionForkGrabBase.h"

namespace uking::action {

ForkGrabBase::ForkGrabBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkGrabBase::~ForkGrabBase() = default;

bool ForkGrabBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkGrabBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkGrabBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkGrabBase::loadParams_() {
    getStaticParam(&mGrabIdx_s, "GrabIdx");
    getStaticParam(&mIsNoGrabSuccess_s, "IsNoGrabSuccess");
}

void ForkGrabBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
