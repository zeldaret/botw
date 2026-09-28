#include "Game/Actor/Action/actionPlayerAreaInOutSendMessage.h"

namespace uking::action {

PlayerAreaInOutSendMessage::PlayerAreaInOutSendMessage(const InitArg& arg)
    : AreaInOutSendMessage(arg) {}

PlayerAreaInOutSendMessage::~PlayerAreaInOutSendMessage() = default;

bool PlayerAreaInOutSendMessage::init_(sead::Heap* heap) {
    return AreaInOutSendMessage::init_(heap);
}

void PlayerAreaInOutSendMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaInOutSendMessage::enter_(params);
}

void PlayerAreaInOutSendMessage::leave_() {
    AreaInOutSendMessage::leave_();
}

void PlayerAreaInOutSendMessage::loadParams_() {
    AreaInOutSendMessage::loadParams_();
    getStaticParam(&mMessageSet_s, "MessageSet");
}

void PlayerAreaInOutSendMessage::calc_() {
    AreaInOutSendMessage::calc_();
}

}  // namespace uking::action
