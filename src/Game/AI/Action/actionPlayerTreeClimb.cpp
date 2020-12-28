#include "Game/AI/Action/actionPlayerTreeClimb.h"

namespace uking::action {

PlayerTreeClimb::PlayerTreeClimb(const InitArg& arg) : PlayerAction(arg) {}

void PlayerTreeClimb::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerTreeClimb::leave_() {
    PlayerAction::leave_();
}

void PlayerTreeClimb::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
