#include "Game/AI/Action/actionPlayerAreaInOutSendMessage.h"

namespace uking::action {

PlayerAreaInOutSendMessage::PlayerAreaInOutSendMessage(const InitArg& arg)
    : ActorAreaInOutSendMessage(arg) {}

PlayerAreaInOutSendMessage::~PlayerAreaInOutSendMessage() = default;

bool PlayerAreaInOutSendMessage::init_(sead::Heap* heap) {
    return ActorAreaInOutSendMessage::init_(heap);
}

void PlayerAreaInOutSendMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    ActorAreaInOutSendMessage::enter_(params);
}

void PlayerAreaInOutSendMessage::leave_() {
    ActorAreaInOutSendMessage::leave_();
}

void PlayerAreaInOutSendMessage::loadParams_() {
    ActorAreaInOutSendMessage::loadParams_();
    getStaticParam(&mMessageSet_s, "MessageSet");
}

void PlayerAreaInOutSendMessage::calc_() {
    ActorAreaInOutSendMessage::calc_();
}

}  // namespace uking::action
