#include "Game/AI/Action/actionSceneSoundKillDuckingAction.h"

namespace uking::action {

SceneSoundKillDuckingAction::SceneSoundKillDuckingAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundKillDuckingAction::~SceneSoundKillDuckingAction() = default;

bool SceneSoundKillDuckingAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundKillDuckingAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SceneSoundKillDuckingAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SceneSoundKillDuckingAction::loadParams_() {
    getDynamicParam(&mDuckerType_d, "DuckerType");
}

void SceneSoundKillDuckingAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
