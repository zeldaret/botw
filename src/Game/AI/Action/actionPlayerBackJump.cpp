#include "Game/AI/Action/actionPlayerBackJump.h"

namespace uking::action {

PlayerBackJump::PlayerBackJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerBackJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerBackJump::leave_() {
    PlayerAction::leave_();
}

void PlayerBackJump::loadParams_() {
    getStaticParam(&mBJSpeedF_s, "BJSpeedF");
    getStaticParam(&mBJHeight_s, "BJHeight");
    getStaticParam(&mNoDamageTime_s, "NoDamageTime");
    getStaticParam(&mJustAvoidTime_s, "JustAvoidTime");
    getStaticParam(&mForceSlowTime_s, "ForceSlowTime");
    getStaticParam(&mMySlowStartFrame_s, "MySlowStartFrame");
    getDynamicParam(&mEnableSwordInput_d, "EnableSwordInput");
}

void PlayerBackJump::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
