#include "Game/AI/Action/actionPlayerCutAfterJump.h"

namespace uking::action {

PlayerCutAfterJump::PlayerCutAfterJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutAfterJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutAfterJump::leave_() {
    PlayerAction::leave_();
}

void PlayerCutAfterJump::loadParams_() {}

void PlayerCutAfterJump::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
