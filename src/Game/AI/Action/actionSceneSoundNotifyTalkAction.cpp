#include "Game/AI/Action/actionSceneSoundNotifyTalkAction.h"

namespace uking::action {

SceneSoundNotifyTalkAction::SceneSoundNotifyTalkAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundNotifyTalkAction::~SceneSoundNotifyTalkAction() = default;

bool SceneSoundNotifyTalkAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundNotifyTalkAction::loadParams_() {
    getDynamicParam(&mCtrlType_d, "CtrlType");
}

}  // namespace uking::action
