#include "Game/AI/Action/actionPlayerLadderJumpLand.h"

namespace uking::action {

PlayerLadderJumpLand::PlayerLadderJumpLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLadderJumpLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLadderJumpLand::leave_() {
    PlayerAction::leave_();
}

void PlayerLadderJumpLand::loadParams_() {
    getDynamicParam(&mMoveDir_d, "MoveDir");
}

void PlayerLadderJumpLand::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
