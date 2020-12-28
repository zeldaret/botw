#include "Game/AI/Action/actionPlayerSideStepLand.h"

namespace uking::action {

PlayerSideStepLand::PlayerSideStepLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSideStepLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSideStepLand::leave_() {
    PlayerAction::leave_();
}

void PlayerSideStepLand::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
