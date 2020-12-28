#include "Game/AI/Action/actionSceneSoundStopDuckingAction.h"

namespace uking::action {

SceneSoundStopDuckingAction::SceneSoundStopDuckingAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundStopDuckingAction::~SceneSoundStopDuckingAction() = default;

bool SceneSoundStopDuckingAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundStopDuckingAction::loadParams_() {
    getDynamicParam(&mDuckerType_d, "DuckerType");
}

}  // namespace uking::action
