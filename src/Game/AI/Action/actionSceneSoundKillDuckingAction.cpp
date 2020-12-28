#include "Game/AI/Action/actionSceneSoundKillDuckingAction.h"

namespace uking::action {

SceneSoundKillDuckingAction::SceneSoundKillDuckingAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundKillDuckingAction::~SceneSoundKillDuckingAction() = default;

bool SceneSoundKillDuckingAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundKillDuckingAction::loadParams_() {
    getDynamicParam(&mDuckerType_d, "DuckerType");
}

}  // namespace uking::action
