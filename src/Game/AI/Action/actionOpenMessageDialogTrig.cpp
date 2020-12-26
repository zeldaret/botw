#include "Game/AI/Action/actionOpenMessageDialogTrig.h"

namespace uking::action {

OpenMessageDialogTrig::OpenMessageDialogTrig(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenMessageDialogTrig::~OpenMessageDialogTrig() = default;

bool OpenMessageDialogTrig::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenMessageDialogTrig::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenMessageDialogTrig::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenMessageDialogTrig::loadParams_() {
    getDynamicParam(&mCloseDialogOption_d, "CloseDialogOption");
    getDynamicParam(&mIsBecomingSpeaker_d, "IsBecomingSpeaker");
    getDynamicParam(&mIsOverWriteLabelActorName_d, "IsOverWriteLabelActorName");
    getDynamicParam(&mMessageId_d, "MessageId");
}

void OpenMessageDialogTrig::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
