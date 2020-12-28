#include "Game/AI/Action/actionSceneSoundSetEndProcAction.h"

namespace uking::action {

SceneSoundSetEndProcAction::SceneSoundSetEndProcAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundSetEndProcAction::~SceneSoundSetEndProcAction() = default;

bool SceneSoundSetEndProcAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundSetEndProcAction::loadParams_() {
    getDynamicParam(&mCtrlType_d, "CtrlType");
}

}  // namespace uking::action
