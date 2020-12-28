#include "Game/AI/Action/actionPlayerAtnMove.h"

namespace uking::action {

PlayerAtnMove::PlayerAtnMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerAtnMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerAtnMove::leave_() {
    PlayerAction::leave_();
}

void PlayerAtnMove::loadParams_() {}

void PlayerAtnMove::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
