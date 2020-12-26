#include "Game/AI/Action/actionPlayerLadderDownStart.h"

namespace uking::action {

PlayerLadderDownStart::PlayerLadderDownStart(const InitArg& arg) : PlayerAction(arg) {}

PlayerLadderDownStart::~PlayerLadderDownStart() = default;

bool PlayerLadderDownStart::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerLadderDownStart::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLadderDownStart::leave_() {
    PlayerAction::leave_();
}

void PlayerLadderDownStart::loadParams_() {}

void PlayerLadderDownStart::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
