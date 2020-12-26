#include "Game/AI/Action/actionSceneSoundNotifyTalkAction.h"

namespace uking::action {

SceneSoundNotifyTalkAction::SceneSoundNotifyTalkAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundNotifyTalkAction::~SceneSoundNotifyTalkAction() = default;

bool SceneSoundNotifyTalkAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundNotifyTalkAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SceneSoundNotifyTalkAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SceneSoundNotifyTalkAction::loadParams_() {
    getDynamicParam(&mCtrlType_d, "CtrlType");
}

void SceneSoundNotifyTalkAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
