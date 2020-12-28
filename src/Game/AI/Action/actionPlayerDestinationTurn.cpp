#include "Game/AI/Action/actionPlayerDestinationTurn.h"

namespace uking::action {

PlayerDestinationTurn::PlayerDestinationTurn(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDestinationTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDestinationTurn::leave_() {
    PlayerAction::leave_();
}

void PlayerDestinationTurn::loadParams_() {
    getDynamicParam(&mDestPosX_d, "DestPosX");
    getDynamicParam(&mDestPosY_d, "DestPosY");
    getDynamicParam(&mDestPosZ_d, "DestPosZ");
}

void PlayerDestinationTurn::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
