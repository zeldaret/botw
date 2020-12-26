#include "Game/AI/Action/actionWaitWhileCreatingOwnedHorse.h"

namespace uking::action {

WaitWhileCreatingOwnedHorse::WaitWhileCreatingOwnedHorse(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

WaitWhileCreatingOwnedHorse::~WaitWhileCreatingOwnedHorse() = default;

bool WaitWhileCreatingOwnedHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitWhileCreatingOwnedHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitWhileCreatingOwnedHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitWhileCreatingOwnedHorse::loadParams_() {}

void WaitWhileCreatingOwnedHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
