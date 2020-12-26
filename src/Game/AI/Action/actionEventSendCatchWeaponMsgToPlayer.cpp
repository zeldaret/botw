#include "Game/AI/Action/actionEventSendCatchWeaponMsgToPlayer.h"

namespace uking::action {

EventSendCatchWeaponMsgToPlayer::EventSendCatchWeaponMsgToPlayer(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSendCatchWeaponMsgToPlayer::~EventSendCatchWeaponMsgToPlayer() = default;

bool EventSendCatchWeaponMsgToPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSendCatchWeaponMsgToPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSendCatchWeaponMsgToPlayer::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSendCatchWeaponMsgToPlayer::loadParams_() {}

void EventSendCatchWeaponMsgToPlayer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
