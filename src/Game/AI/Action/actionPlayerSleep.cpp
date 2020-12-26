#include "Game/AI/Action/actionPlayerSleep.h"

namespace uking::action {

PlayerSleep::PlayerSleep(const InitArg& arg) : PlayerAction(arg) {}

PlayerSleep::~PlayerSleep() = default;

bool PlayerSleep::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSleep::leave_() {
    PlayerAction::leave_();
}

void PlayerSleep::loadParams_() {}

void PlayerSleep::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
