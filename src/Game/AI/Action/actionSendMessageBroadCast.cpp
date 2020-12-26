#include "Game/AI/Action/actionSendMessageBroadCast.h"

namespace uking::action {

SendMessageBroadCast::SendMessageBroadCast(const InitArg& arg) : SendMessage(arg) {}

SendMessageBroadCast::~SendMessageBroadCast() = default;

bool SendMessageBroadCast::init_(sead::Heap* heap) {
    return SendMessage::init_(heap);
}

void SendMessageBroadCast::enter_(ksys::act::ai::InlineParamPack* params) {
    SendMessage::enter_(params);
}

void SendMessageBroadCast::leave_() {
    SendMessage::leave_();
}

void SendMessageBroadCast::loadParams_() {
    SendMessage::loadParams_();
    getStaticParam(&mMsgType_s, "MsgType");
}

void SendMessageBroadCast::calc_() {
    SendMessage::calc_();
}

}  // namespace uking::action
