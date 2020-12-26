#include "Game/AI/Action/actionSendMessage4YunBoCannon.h"

namespace uking::action {

SendMessage4YunBoCannon::SendMessage4YunBoCannon(const InitArg& arg) : SendMessage(arg) {}

SendMessage4YunBoCannon::~SendMessage4YunBoCannon() = default;

bool SendMessage4YunBoCannon::init_(sead::Heap* heap) {
    return SendMessage::init_(heap);
}

void SendMessage4YunBoCannon::enter_(ksys::act::ai::InlineParamPack* params) {
    SendMessage::enter_(params);
}

void SendMessage4YunBoCannon::leave_() {
    SendMessage::leave_();
}

void SendMessage4YunBoCannon::loadParams_() {
    SendMessage::loadParams_();
    getStaticParam(&mMsgType_s, "MsgType");
}

void SendMessage4YunBoCannon::calc_() {
    SendMessage::calc_();
}

}  // namespace uking::action
