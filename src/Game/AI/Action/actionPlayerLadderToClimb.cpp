#include "Game/AI/Action/actionPlayerLadderToClimb.h"

namespace uking::action {

PlayerLadderToClimb::PlayerLadderToClimb(const InitArg& arg) : PlayerAction(arg) {}

PlayerLadderToClimb::~PlayerLadderToClimb() = default;

bool PlayerLadderToClimb::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerLadderToClimb::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLadderToClimb::leave_() {
    PlayerAction::leave_();
}

void PlayerLadderToClimb::loadParams_() {}

void PlayerLadderToClimb::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
