#include "Game/AI/Action/actionSetupGetDemoModeNumUi.h"

namespace uking::action {

SetupGetDemoModeNumUi::SetupGetDemoModeNumUi(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetupGetDemoModeNumUi::~SetupGetDemoModeNumUi() = default;

bool SetupGetDemoModeNumUi::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetupGetDemoModeNumUi::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetupGetDemoModeNumUi::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetupGetDemoModeNumUi::loadParams_() {
    getDynamicParam(&mNumUiType_d, "NumUiType");
    getDynamicParam(&mAddNum_d, "AddNum");
}

void SetupGetDemoModeNumUi::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
