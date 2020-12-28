#include "Game/AI/Action/actionSceneSoundCtrlAction.h"

namespace uking::action {

SceneSoundCtrlAction::SceneSoundCtrlAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SceneSoundCtrlAction::~SceneSoundCtrlAction() = default;

bool SceneSoundCtrlAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundCtrlAction::loadParams_() {
    getDynamicParam(&mBgmCtrlType_d, "BgmCtrlType");
    getDynamicParam(&mSeCtrlType_d, "SeCtrlType");
}

}  // namespace uking::action
