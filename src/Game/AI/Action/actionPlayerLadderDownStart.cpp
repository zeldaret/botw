#include "Game/AI/Action/actionPlayerLadderDownStart.h"

namespace uking::action {

PlayerLadderDownStart::PlayerLadderDownStart(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLadderDownStart::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLadderDownStart::leave_() {
    PlayerAction::leave_();
}

void PlayerLadderDownStart::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
