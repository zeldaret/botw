#include "Game/AI/Action/actionPlayerSuperJump.h"

namespace uking::action {

PlayerSuperJump::PlayerSuperJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSuperJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSuperJump::leave_() {
    PlayerAction::leave_();
}

void PlayerSuperJump::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mWindScale_s, "WindScale");
}

void PlayerSuperJump::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
