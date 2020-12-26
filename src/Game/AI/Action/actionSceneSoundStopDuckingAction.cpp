#include "Game/AI/Action/actionSceneSoundStopDuckingAction.h"

namespace uking::action {

SceneSoundStopDuckingAction::SceneSoundStopDuckingAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundStopDuckingAction::~SceneSoundStopDuckingAction() = default;

bool SceneSoundStopDuckingAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundStopDuckingAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SceneSoundStopDuckingAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SceneSoundStopDuckingAction::loadParams_() {
    getDynamicParam(&mDuckerType_d, "DuckerType");
}

void SceneSoundStopDuckingAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
