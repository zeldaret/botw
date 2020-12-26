#include "Game/AI/Action/actionSendPlayerNoticeMessageBase.h"

namespace uking::action {

SendPlayerNoticeMessageBase::SendPlayerNoticeMessageBase(const InitArg& arg)
    : OnetimeStopASPlay(arg) {}

SendPlayerNoticeMessageBase::~SendPlayerNoticeMessageBase() = default;

bool SendPlayerNoticeMessageBase::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void SendPlayerNoticeMessageBase::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void SendPlayerNoticeMessageBase::leave_() {
    OnetimeStopASPlay::leave_();
}

void SendPlayerNoticeMessageBase::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mTargetActorName_s, "TargetActorName");
}

void SendPlayerNoticeMessageBase::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action
