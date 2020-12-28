#include "Game/AI/Action/actionPlayerWakeBoard.h"

namespace uking::action {

PlayerWakeBoard::PlayerWakeBoard(const InitArg& arg) : PlayerAction(arg) {}

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
