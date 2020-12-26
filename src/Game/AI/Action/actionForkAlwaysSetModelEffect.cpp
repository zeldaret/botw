#include "Game/AI/Action/actionForkAlwaysSetModelEffect.h"

namespace uking::action {

ForkAlwaysSetModelEffect::ForkAlwaysSetModelEffect(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkAlwaysSetModelEffect::~ForkAlwaysSetModelEffect() = default;

bool ForkAlwaysSetModelEffect::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAlwaysSetModelEffect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAlwaysSetModelEffect::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAlwaysSetModelEffect::loadParams_() {
    getStaticParam(&mTimer_s, "Timer");
}

void ForkAlwaysSetModelEffect::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
