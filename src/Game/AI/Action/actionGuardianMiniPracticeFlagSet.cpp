#include "Game/AI/Action/actionGuardianMiniPracticeFlagSet.h"

namespace uking::action {

GuardianMiniPracticeFlagSet::GuardianMiniPracticeFlagSet(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

GuardianMiniPracticeFlagSet::~GuardianMiniPracticeFlagSet() = default;

bool GuardianMiniPracticeFlagSet::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GuardianMiniPracticeFlagSet::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GuardianMiniPracticeFlagSet::leave_() {
    ksys::act::ai::Action::leave_();
}

void GuardianMiniPracticeFlagSet::loadParams_() {
    getAITreeVariable(&mGuardianMiniPracticeState_a, "GuardianMiniPracticeState");
}

void GuardianMiniPracticeFlagSet::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
