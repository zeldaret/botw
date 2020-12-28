#include "Game/AI/Action/actionEventSendCatchWeaponMsgToPlayer.h"

namespace uking::action {

EventSendCatchWeaponMsgToPlayer::EventSendCatchWeaponMsgToPlayer(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSendCatchWeaponMsgToPlayer::~EventSendCatchWeaponMsgToPlayer() = default;

bool EventSendCatchWeaponMsgToPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSendCatchWeaponMsgToPlayer::loadParams_() {}

}  // namespace uking::action
