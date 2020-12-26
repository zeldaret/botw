#include "Game/AI/Action/actionPlayerLadderDownEnd.h"

namespace uking::action {

PlayerLadderDownEnd::PlayerLadderDownEnd(const InitArg& arg) : PlayerAction(arg) {}

PlayerLadderDownEnd::~PlayerLadderDownEnd() = default;

bool PlayerLadderDownEnd::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerLadderDownEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLadderDownEnd::leave_() {
    PlayerAction::leave_();
}

void PlayerLadderDownEnd::loadParams_() {}

void PlayerLadderDownEnd::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
