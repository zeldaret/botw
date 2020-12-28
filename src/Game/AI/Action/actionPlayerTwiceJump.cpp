#include "Game/AI/Action/actionPlayerTwiceJump.h"

namespace uking::action {

PlayerTwiceJump::PlayerTwiceJump(const InitArg& arg) : PlayerFall(arg) {}

void PlayerTwiceJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerFall::enter_(params);
}

void PlayerTwiceJump::leave_() {
    PlayerFall::leave_();
}

void PlayerTwiceJump::loadParams_() {
    PlayerFall::loadParams_();
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerTwiceJump::calc_() {
    PlayerFall::calc_();
}

}  // namespace uking::action
