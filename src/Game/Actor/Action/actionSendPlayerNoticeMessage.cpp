#include "Game/Actor/Action/actionSendPlayerNoticeMessage.h"

namespace uking::action {

SendPlayerNoticeMessage::SendPlayerNoticeMessage(const InitArg& arg) : SendNoticeMessageBase(arg) {}

SendPlayerNoticeMessage::~SendPlayerNoticeMessage() = default;

bool SendPlayerNoticeMessage::init_(sead::Heap* heap) {
    return SendNoticeMessageBase::init_(heap);
}

void SendPlayerNoticeMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    SendNoticeMessageBase::enter_(params);
}

void SendPlayerNoticeMessage::leave_() {
    SendNoticeMessageBase::leave_();
}

void SendPlayerNoticeMessage::loadParams_() {
    SendNoticeMessageBase::loadParams_();
}

void SendPlayerNoticeMessage::calc_() {
    SendNoticeMessageBase::calc_();
}

}  // namespace uking::action
