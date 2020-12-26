#include "Game/AI/Action/actionSendPlayerNoticeMessage.h"

namespace uking::action {

SendPlayerNoticeMessage::SendPlayerNoticeMessage(const InitArg& arg)
    : SendPlayerNoticeMessageBase(arg) {}

SendPlayerNoticeMessage::~SendPlayerNoticeMessage() = default;

bool SendPlayerNoticeMessage::init_(sead::Heap* heap) {
    return SendPlayerNoticeMessageBase::init_(heap);
}

void SendPlayerNoticeMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    SendPlayerNoticeMessageBase::enter_(params);
}

void SendPlayerNoticeMessage::leave_() {
    SendPlayerNoticeMessageBase::leave_();
}

void SendPlayerNoticeMessage::loadParams_() {
    SendPlayerNoticeMessageBase::loadParams_();
}

void SendPlayerNoticeMessage::calc_() {
    SendPlayerNoticeMessageBase::calc_();
}

}  // namespace uking::action
