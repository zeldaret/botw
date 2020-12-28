#include "Game/AI/Action/actionPlayerDrown.h"

namespace uking::action {

PlayerDrown::PlayerDrown(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDrown::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDrown::leave_() {
    PlayerAction::leave_();
}

void PlayerDrown::loadParams_() {}

void PlayerDrown::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
