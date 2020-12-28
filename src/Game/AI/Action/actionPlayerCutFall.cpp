#include "Game/AI/Action/actionPlayerCutFall.h"

namespace uking::action {

PlayerCutFall::PlayerCutFall(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutFall::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutFall::leave_() {
    PlayerAction::leave_();
}

void PlayerCutFall::loadParams_() {
    getStaticParam(&mParashawlInvalidTime_s, "ParashawlInvalidTime");
    getStaticParam(&mFallSpAttackHeight_s, "FallSpAttackHeight");
    getStaticParam(&mFallSpAttackRadiusMin_s, "FallSpAttackRadiusMin");
    getStaticParam(&mFallSpAttackRadiusMax_s, "FallSpAttackRadiusMax");
    getStaticParam(&mFallSpAttackRadiusAdd_s, "FallSpAttackRadiusAdd");
    getStaticParam(&mFallSpAttackRadiusAddLSword_s, "FallSpAttackRadiusAddLSword");
    getStaticParam(&mFallSpLargeAttackRadius_s, "FallSpLargeAttackRadius");
    getStaticParam(&mRumbleType_s, "RumbleType");
    getStaticParam(&mRumblePowerMin_s, "RumblePowerMin");
    getStaticParam(&mRumblePowerMax_s, "RumblePowerMax");
}

void PlayerCutFall::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
