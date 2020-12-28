#include "Game/AI/Action/actionSetupGetDemoModeNumUi.h"

namespace uking::action {

SetupGetDemoModeNumUi::SetupGetDemoModeNumUi(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetupGetDemoModeNumUi::~SetupGetDemoModeNumUi() = default;

bool SetupGetDemoModeNumUi::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetupGetDemoModeNumUi::loadParams_() {
    getDynamicParam(&mNumUiType_d, "NumUiType");
    getDynamicParam(&mAddNum_d, "AddNum");
}

}  // namespace uking::action
