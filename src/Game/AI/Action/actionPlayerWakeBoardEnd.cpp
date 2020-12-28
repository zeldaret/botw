#include "Game/AI/Action/actionPlayerWakeBoardEnd.h"

namespace uking::action {

PlayerWakeBoardEnd::PlayerWakeBoardEnd(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWakeBoardEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWakeBoardEnd::leave_() {
    PlayerAction::leave_();
}

void PlayerWakeBoardEnd::loadParams_() {}

void PlayerWakeBoardEnd::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
