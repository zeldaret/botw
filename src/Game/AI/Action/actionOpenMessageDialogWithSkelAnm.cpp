#include "Game/AI/Action/actionOpenMessageDialogWithSkelAnm.h"

namespace uking::action {

OpenMessageDialogWithSkelAnm::OpenMessageDialogWithSkelAnm(const InitArg& arg)
    : OpenMessageDialogBase(arg) {}

OpenMessageDialogWithSkelAnm::~OpenMessageDialogWithSkelAnm() = default;

bool OpenMessageDialogWithSkelAnm::init_(sead::Heap* heap) {
    return OpenMessageDialogBase::init_(heap);
}

void OpenMessageDialogWithSkelAnm::enter_(ksys::act::ai::InlineParamPack* params) {
    OpenMessageDialogBase::enter_(params);
}

void OpenMessageDialogWithSkelAnm::leave_() {
    OpenMessageDialogBase::leave_();
}

void OpenMessageDialogWithSkelAnm::loadParams_() {
    OpenMessageDialogBase::loadParams_();
    getDynamicParam(&mAnimName_d, "AnimName");
}

void OpenMessageDialogWithSkelAnm::calc_() {
    OpenMessageDialogBase::calc_();
}

}  // namespace uking::action
