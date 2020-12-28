#include "Game/AI/Action/actionPlayerSelfCamera.h"

namespace uking::action {

PlayerSelfCamera::PlayerSelfCamera(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSelfCamera::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSelfCamera::leave_() {
    PlayerAction::leave_();
}

void PlayerSelfCamera::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
