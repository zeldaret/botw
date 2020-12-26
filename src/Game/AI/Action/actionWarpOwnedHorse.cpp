#include "Game/AI/Action/actionWarpOwnedHorse.h"

namespace uking::action {

WarpOwnedHorse::WarpOwnedHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpOwnedHorse::~WarpOwnedHorse() = default;

bool WarpOwnedHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpOwnedHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WarpOwnedHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpOwnedHorse::loadParams_() {}

void WarpOwnedHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
