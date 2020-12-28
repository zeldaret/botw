#include "Game/AI/Action/actionPlayerRemainsBlow.h"

namespace uking::action {

PlayerRemainsBlow::PlayerRemainsBlow(const InitArg& arg) : PlayerAction(arg) {}

void PlayerRemainsBlow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerRemainsBlow::leave_() {
    PlayerAction::leave_();
}

void PlayerRemainsBlow::loadParams_() {
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerRemainsBlow::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
