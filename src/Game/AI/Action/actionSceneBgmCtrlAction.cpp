#include "Game/AI/Action/actionSceneBgmCtrlAction.h"

namespace uking::action {

SceneBgmCtrlAction::SceneBgmCtrlAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SceneBgmCtrlAction::~SceneBgmCtrlAction() = default;

bool SceneBgmCtrlAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneBgmCtrlAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SceneBgmCtrlAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SceneBgmCtrlAction::loadParams_() {
    getDynamicParam(&mCtrlType_d, "CtrlType");
}

void SceneBgmCtrlAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
