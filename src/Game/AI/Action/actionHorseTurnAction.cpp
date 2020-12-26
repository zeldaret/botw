#include "Game/AI/Action/actionHorseTurnAction.h"

namespace uking::action {

HorseTurnAction::HorseTurnAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseTurnAction::~HorseTurnAction() = default;

bool HorseTurnAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseTurnAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseTurnAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseTurnAction::loadParams_() {
    getStaticParam(&mGoalDegToleranceAtEnter_s, "GoalDegToleranceAtEnter");
    getStaticParam(&mGoalDegTolerance_s, "GoalDegTolerance");
    getDynamicParam(&mTargetDirection_d, "TargetDirection");
}

void HorseTurnAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
