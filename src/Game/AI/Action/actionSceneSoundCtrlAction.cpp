#include "Game/AI/Action/actionSceneSoundCtrlAction.h"

namespace uking::action {

SceneSoundCtrlAction::SceneSoundCtrlAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SceneSoundCtrlAction::~SceneSoundCtrlAction() = default;

bool SceneSoundCtrlAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundCtrlAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SceneSoundCtrlAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SceneSoundCtrlAction::loadParams_() {
    getDynamicParam(&mBgmCtrlType_d, "BgmCtrlType");
    getDynamicParam(&mSeCtrlType_d, "SeCtrlType");
}

void SceneSoundCtrlAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
