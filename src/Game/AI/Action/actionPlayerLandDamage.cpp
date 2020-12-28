#include "Game/AI/Action/actionPlayerLandDamage.h"

namespace uking::action {

PlayerLandDamage::PlayerLandDamage(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLandDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLandDamage::leave_() {
    PlayerAction::leave_();
}

void PlayerLandDamage::loadParams_() {
    getStaticParam(&mWaitTimeMin_s, "WaitTimeMin");
    getStaticParam(&mWaitTimeMax_s, "WaitTimeMax");
    getStaticParam(&mDeadHeight_s, "DeadHeight");
    getStaticParam(&mDamageMin_s, "DamageMin");
}

void PlayerLandDamage::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
