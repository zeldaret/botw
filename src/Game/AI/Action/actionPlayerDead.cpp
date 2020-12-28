#include "Game/AI/Action/actionPlayerDead.h"

namespace uking::action {

PlayerDead::PlayerDead(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDead::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDead::leave_() {
    PlayerAction::leave_();
}

void PlayerDead::loadParams_() {
    getStaticParam(&mRagdollChangeTime_s, "RagdollChangeTime");
}

void PlayerDead::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
