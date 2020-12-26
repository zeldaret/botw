#include "Game/AI/Action/actionOpenGetDemoDialogDressFairy.h"

namespace uking::action {

OpenGetDemoDialogDressFairy::OpenGetDemoDialogDressFairy(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

OpenGetDemoDialogDressFairy::~OpenGetDemoDialogDressFairy() = default;

bool OpenGetDemoDialogDressFairy::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenGetDemoDialogDressFairy::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenGetDemoDialogDressFairy::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenGetDemoDialogDressFairy::loadParams_() {}

void OpenGetDemoDialogDressFairy::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
