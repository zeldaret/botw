#include "Game/AI/Action/actionOpenGetDemoDialog.h"

namespace uking::action {

OpenGetDemoDialog::OpenGetDemoDialog(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenGetDemoDialog::~OpenGetDemoDialog() = default;

bool OpenGetDemoDialog::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenGetDemoDialog::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenGetDemoDialog::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenGetDemoDialog::loadParams_() {
    getDynamicParam(&mIsInvalidOpenPouch_d, "IsInvalidOpenPouch");
    getDynamicParam(&mUseLastTryGetItemName_d, "UseLastTryGetItemName");
    getDynamicParam(&mEnableMultiGet_d, "EnableMultiGet");
    getDynamicParam(&mTargetActorName_d, "TargetActorName");
}

void OpenGetDemoDialog::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
