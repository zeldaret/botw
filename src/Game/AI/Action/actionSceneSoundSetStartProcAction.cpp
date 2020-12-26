#include "Game/AI/Action/actionSceneSoundSetStartProcAction.h"

namespace uking::action {

SceneSoundSetStartProcAction::SceneSoundSetStartProcAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundSetStartProcAction::~SceneSoundSetStartProcAction() = default;

bool SceneSoundSetStartProcAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundSetStartProcAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SceneSoundSetStartProcAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SceneSoundSetStartProcAction::loadParams_() {
    getDynamicParam(&mBgmCtrlType_d, "BgmCtrlType");
    getDynamicParam(&mSeCtrlType_d, "SeCtrlType");
}

void SceneSoundSetStartProcAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
