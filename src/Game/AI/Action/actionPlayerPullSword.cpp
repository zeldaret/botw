#include "Game/AI/Action/actionPlayerPullSword.h"

namespace uking::action {

PlayerPullSword::PlayerPullSword(const InitArg& arg) : PlayerAction(arg) {}

void PlayerPullSword::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerPullSword::leave_() {
    PlayerAction::leave_();
}

void PlayerPullSword::loadParams_() {
    getStaticParam(&mLifeDecInterval1_s, "LifeDecInterval1");
    getStaticParam(&mLifeDecInterval2_s, "LifeDecInterval2");
    getStaticParam(&mLifeDecInterval3_s, "LifeDecInterval3");
    getStaticParam(&mLifeDecInterval4_s, "LifeDecInterval4");
    getStaticParam(&mLifeDecInterval5_s, "LifeDecInterval5");
    getStaticParam(&mInterruptInterval_s, "InterruptInterval");
    getStaticParam(&mSuccessLife_s, "SuccessLife");
}

void PlayerPullSword::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
