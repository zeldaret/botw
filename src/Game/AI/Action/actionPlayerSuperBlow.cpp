#include "Game/AI/Action/actionPlayerSuperBlow.h"

namespace uking::action {

PlayerSuperBlow::PlayerSuperBlow(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSuperBlow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSuperBlow::leave_() {
    PlayerAction::leave_();
}

void PlayerSuperBlow::loadParams_() {
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mDecSpeed_s, "DecSpeed");
    getStaticParam(&mNoRagdollTime_s, "NoRagdollTime");
}

void PlayerSuperBlow::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
