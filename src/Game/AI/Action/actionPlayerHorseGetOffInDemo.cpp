#include "Game/AI/Action/actionPlayerHorseGetOffInDemo.h"

namespace uking::action {

PlayerHorseGetOffInDemo::PlayerHorseGetOffInDemo(const InitArg& arg) : PlayerAction(arg) {}

void PlayerHorseGetOffInDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerHorseGetOffInDemo::leave_() {
    PlayerAction::leave_();
}

void PlayerHorseGetOffInDemo::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
