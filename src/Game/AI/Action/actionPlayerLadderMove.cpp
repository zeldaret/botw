#include "Game/AI/Action/actionPlayerLadderMove.h"

namespace uking::action {

PlayerLadderMove::PlayerLadderMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLadderMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLadderMove::leave_() {
    PlayerAction::leave_();
}

void PlayerLadderMove::loadParams_() {
    getStaticParam(&mDownMoveSpeed_s, "DownMoveSpeed");
}

void PlayerLadderMove::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
