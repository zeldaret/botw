#include "Game/AI/Action/actionIdleAction.h"

namespace uking::action {

IdleAction::IdleAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IdleAction::~IdleAction() = default;

bool IdleAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IdleAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void IdleAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void IdleAction::loadParams_() {
    getDynamicParam(&mDisablePhysics_d, "DisablePhysics");
}

void IdleAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
