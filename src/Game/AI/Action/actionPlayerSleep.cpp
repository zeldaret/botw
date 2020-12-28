#include "Game/AI/Action/actionPlayerSleep.h"

namespace uking::action {

PlayerSleep::PlayerSleep(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSleep::leave_() {
    PlayerAction::leave_();
}

void PlayerSleep::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
