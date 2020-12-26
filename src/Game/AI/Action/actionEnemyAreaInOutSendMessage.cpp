#include "Game/AI/Action/actionEnemyAreaInOutSendMessage.h"

namespace uking::action {

EnemyAreaInOutSendMessage::EnemyAreaInOutSendMessage(const InitArg& arg)
    : ActorAreaInOutSendMessage(arg) {}

EnemyAreaInOutSendMessage::~EnemyAreaInOutSendMessage() = default;

bool EnemyAreaInOutSendMessage::init_(sead::Heap* heap) {
    return ActorAreaInOutSendMessage::init_(heap);
}

void EnemyAreaInOutSendMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    ActorAreaInOutSendMessage::enter_(params);
}

void EnemyAreaInOutSendMessage::leave_() {
    ActorAreaInOutSendMessage::leave_();
}

void EnemyAreaInOutSendMessage::loadParams_() {
    ActorAreaInOutSendMessage::loadParams_();
    getStaticParam(&mMessageID_s, "MessageID");
}

void EnemyAreaInOutSendMessage::calc_() {
    ActorAreaInOutSendMessage::calc_();
}

}  // namespace uking::action
