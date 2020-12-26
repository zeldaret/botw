#include "Game/AI/Action/actionOpenMessageDialogBase.h"

namespace uking::action {

OpenMessageDialogBase::OpenMessageDialogBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenMessageDialogBase::~OpenMessageDialogBase() = default;

bool OpenMessageDialogBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenMessageDialogBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenMessageDialogBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenMessageDialogBase::loadParams_() {
    getDynamicParam(&mCloseDialogOption_d, "CloseDialogOption");
    getDynamicParam(&mMessageOpenDelayTime_d, "MessageOpenDelayTime");
    getDynamicParam(&mIsCloseMessageDialog_d, "IsCloseMessageDialog");
    getDynamicParam(&mIsBecomingSpeaker_d, "IsBecomingSpeaker");
    getDynamicParam(&mIsOverWriteLabelActorName_d, "IsOverWriteLabelActorName");
    getDynamicParam(&mIsWaitAS_d, "IsWaitAS");
    getDynamicParam(&mMessageId_d, "MessageId");
}

void OpenMessageDialogBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
