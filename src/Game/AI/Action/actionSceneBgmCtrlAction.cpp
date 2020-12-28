#include "Game/AI/Action/actionSceneBgmCtrlAction.h"

namespace uking::action {

SceneBgmCtrlAction::SceneBgmCtrlAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SceneBgmCtrlAction::~SceneBgmCtrlAction() = default;

bool SceneBgmCtrlAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneBgmCtrlAction::loadParams_() {
    getDynamicParam(&mCtrlType_d, "CtrlType");
}

}  // namespace uking::action
