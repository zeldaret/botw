#include "Game/AI/Action/actionSceneSoundStartDuckingAction.h"

namespace uking::action {

SceneSoundStartDuckingAction::SceneSoundStartDuckingAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundStartDuckingAction::~SceneSoundStartDuckingAction() = default;

bool SceneSoundStartDuckingAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundStartDuckingAction::loadParams_() {
    getDynamicParam(&mDuckerType_d, "DuckerType");
}

}  // namespace uking::action
