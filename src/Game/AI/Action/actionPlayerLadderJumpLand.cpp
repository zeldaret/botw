#include "Game/AI/Action/actionPlayerLadderJumpLand.h"

namespace uking::action {

PlayerLadderJumpLand::PlayerLadderJumpLand(const InitArg& arg) : PlayerAction(arg) {}

PlayerLadderJumpLand::~PlayerLadderJumpLand() = default;

bool PlayerLadderJumpLand::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

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
