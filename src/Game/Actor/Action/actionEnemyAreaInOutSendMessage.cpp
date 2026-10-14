#include "Game/Actor/Action/actionEnemyAreaInOutSendMessage.h"

namespace uking::action {

EnemyAreaInOutSendMessage::EnemyAreaInOutSendMessage(const InitArg& arg)
    : AreaInOutSendMessage(arg) {}

EnemyAreaInOutSendMessage::~EnemyAreaInOutSendMessage() = default;

bool EnemyAreaInOutSendMessage::init_(sead::Heap* heap) {
    return AreaInOutSendMessage::init_(heap);
}

void EnemyAreaInOutSendMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaInOutSendMessage::enter_(params);
}

void EnemyAreaInOutSendMessage::leave_() {
    AreaInOutSendMessage::leave_();
}

void EnemyAreaInOutSendMessage::loadParams_() {
    AreaInOutSendMessage::loadParams_();
    getStaticParam(&mMessageID_s, "MessageID");
}

void EnemyAreaInOutSendMessage::calc_() {
    AreaInOutSendMessage::calc_();
}

}  // namespace uking::action
