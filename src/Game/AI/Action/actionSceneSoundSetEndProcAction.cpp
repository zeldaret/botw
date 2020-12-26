#include "Game/AI/Action/actionSceneSoundSetEndProcAction.h"

namespace uking::action {

SceneSoundSetEndProcAction::SceneSoundSetEndProcAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundSetEndProcAction::~SceneSoundSetEndProcAction() = default;

bool SceneSoundSetEndProcAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundSetEndProcAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SceneSoundSetEndProcAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SceneSoundSetEndProcAction::loadParams_() {
    getDynamicParam(&mCtrlType_d, "CtrlType");
}

void SceneSoundSetEndProcAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
