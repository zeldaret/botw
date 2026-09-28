#include "Game/Actor/Action/actionSendNoticeMessageBase.h"

namespace uking::action {

SendNoticeMessageBase::SendNoticeMessageBase(const InitArg& arg) : OnetimeStopASPlay(arg) {}

SendNoticeMessageBase::~SendNoticeMessageBase() = default;

bool SendNoticeMessageBase::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void SendNoticeMessageBase::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void SendNoticeMessageBase::leave_() {
    OnetimeStopASPlay::leave_();
}

void SendNoticeMessageBase::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mTargetActorName_s, "TargetActorName");
}

void SendNoticeMessageBase::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action
