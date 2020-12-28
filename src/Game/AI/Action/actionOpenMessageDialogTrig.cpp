#include "Game/AI/Action/actionOpenMessageDialogTrig.h"

namespace uking::action {

OpenMessageDialogTrig::OpenMessageDialogTrig(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenMessageDialogTrig::~OpenMessageDialogTrig() = default;

bool OpenMessageDialogTrig::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenMessageDialogTrig::loadParams_() {
    getDynamicParam(&mCloseDialogOption_d, "CloseDialogOption");
    getDynamicParam(&mIsBecomingSpeaker_d, "IsBecomingSpeaker");
    getDynamicParam(&mIsOverWriteLabelActorName_d, "IsOverWriteLabelActorName");
    getDynamicParam(&mMessageId_d, "MessageId");
}

}  // namespace uking::action
