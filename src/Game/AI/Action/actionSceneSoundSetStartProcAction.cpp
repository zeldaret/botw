#include "Game/AI/Action/actionSceneSoundSetStartProcAction.h"

namespace uking::action {

SceneSoundSetStartProcAction::SceneSoundSetStartProcAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundSetStartProcAction::~SceneSoundSetStartProcAction() = default;

bool SceneSoundSetStartProcAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundSetStartProcAction::loadParams_() {
    getDynamicParam(&mBgmCtrlType_d, "BgmCtrlType");
    getDynamicParam(&mSeCtrlType_d, "SeCtrlType");
}

}  // namespace uking::action
