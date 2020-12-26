#include "Game/AI/Action/actionSceneSoundStartDuckingAction.h"

namespace uking::action {

SceneSoundStartDuckingAction::SceneSoundStartDuckingAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundStartDuckingAction::~SceneSoundStartDuckingAction() = default;

bool SceneSoundStartDuckingAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundStartDuckingAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SceneSoundStartDuckingAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SceneSoundStartDuckingAction::loadParams_() {
    getDynamicParam(&mDuckerType_d, "DuckerType");
}

void SceneSoundStartDuckingAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
