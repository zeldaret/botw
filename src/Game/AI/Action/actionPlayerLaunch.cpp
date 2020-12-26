#include "Game/AI/Action/actionPlayerLaunch.h"

namespace uking::action {

PlayerLaunch::PlayerLaunch(const InitArg& arg) : PlayerAction(arg) {}

PlayerLaunch::~PlayerLaunch() = default;

bool PlayerLaunch::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerLaunch::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLaunch::leave_() {
    PlayerAction::leave_();
}

void PlayerLaunch::loadParams_() {
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mAddLinearImpulse_s, "AddLinearImpulse");
    getStaticParam(&mAddRollImpulse_s, "AddRollImpulse");
    getStaticParam(&mNoRagdollTime_s, "NoRagdollTime");
    getStaticParam(&mDamage_s, "Damage");
    getDynamicParam(&mBasePos_d, "BasePos");
}

void PlayerLaunch::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
