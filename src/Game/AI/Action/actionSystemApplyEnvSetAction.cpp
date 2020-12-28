#include "Game/AI/Action/actionSystemApplyEnvSetAction.h"

namespace uking::action {

SystemApplyEnvSetAction::SystemApplyEnvSetAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SystemApplyEnvSetAction::~SystemApplyEnvSetAction() = default;

void SystemApplyEnvSetAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SystemApplyEnvSetAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SystemApplyEnvSetAction::loadParams_() {
    getDynamicParam(&mEnvSetName_d, "EnvSetName");
}

void SystemApplyEnvSetAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
