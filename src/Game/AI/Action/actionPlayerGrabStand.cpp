#include "Game/AI/Action/actionPlayerGrabStand.h"

namespace uking::action {

PlayerGrabStand::PlayerGrabStand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGrabStand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGrabStand::leave_() {
    PlayerAction::leave_();
}

void PlayerGrabStand::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
