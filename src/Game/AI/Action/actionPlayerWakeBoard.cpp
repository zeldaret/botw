#include "Game/AI/Action/actionPlayerWakeBoard.h"

namespace uking::action {

PlayerWakeBoard::PlayerWakeBoard(const InitArg& arg) : PlayerAction(arg) {}

PlayerWakeBoard::~PlayerWakeBoard() = default;

bool PlayerWakeBoard::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerWakeBoard::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWakeBoard::leave_() {
    PlayerAction::leave_();
}

void PlayerWakeBoard::loadParams_() {}

void PlayerWakeBoard::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
