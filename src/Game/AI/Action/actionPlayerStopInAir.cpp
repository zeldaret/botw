#include "Game/AI/Action/actionPlayerStopInAir.h"

namespace uking::action {

PlayerStopInAir::PlayerStopInAir(const InitArg& arg) : PlayerAction(arg) {}

void PlayerStopInAir::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerStopInAir::leave_() {
    PlayerAction::leave_();
}

void PlayerStopInAir::loadParams_() {
    getDynamicParam(&mNoFixed_d, "NoFixed");
}

void PlayerStopInAir::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
