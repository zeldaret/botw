#include "KingSystem/Sound/Actor/Action/actionSceneSoundKillDuckingAction.h"

namespace ksys::snd {

SceneSoundKillDuckingAction::SceneSoundKillDuckingAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundKillDuckingAction::~SceneSoundKillDuckingAction() = default;

bool SceneSoundKillDuckingAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundKillDuckingAction::loadParams_() {
    getDynamicParam(&mDuckerType_d, "DuckerType");
}

}  // namespace ksys::snd
