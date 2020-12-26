#include "Game/AI/Action/actionForkAddLinearImpulse.h"

namespace uking::action {

ForkAddLinearImpulse::ForkAddLinearImpulse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAddLinearImpulse::~ForkAddLinearImpulse() = default;

bool ForkAddLinearImpulse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAddLinearImpulse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAddLinearImpulse::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAddLinearImpulse::loadParams_() {
    getStaticParam(&mPower_s, "Power");
    getStaticParam(&mDirection_s, "Direction");
}

void ForkAddLinearImpulse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
