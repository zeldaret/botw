#include "Game/AI/Action/actionGuardianMoveTo.h"

namespace uking::action {

GuardianMoveTo::GuardianMoveTo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GuardianMoveTo::~GuardianMoveTo() = default;

bool GuardianMoveTo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GuardianMoveTo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GuardianMoveTo::leave_() {
    ksys::act::ai::Action::leave_();
}

void GuardianMoveTo::loadParams_() {}

void GuardianMoveTo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
