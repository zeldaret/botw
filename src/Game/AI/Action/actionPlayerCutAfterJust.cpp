#include "Game/AI/Action/actionPlayerCutAfterJust.h"

namespace uking::action {

PlayerCutAfterJust::PlayerCutAfterJust(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutAfterJust::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutAfterJust::leave_() {
    PlayerAction::leave_();
}

void PlayerCutAfterJust::loadParams_() {
    getStaticParam(&mSlowContTime_s, "SlowContTime");
    getStaticParam(&mLastCutAcceptTime_s, "LastCutAcceptTime");
    getStaticParam(&mLastCutAcceptTimeLSword_s, "LastCutAcceptTimeLSword");
    getStaticParam(&mLastCutAcceptTimeSpear_s, "LastCutAcceptTimeSpear");
    getStaticParam(&mForceSlowTime_s, "ForceSlowTime");
}

void PlayerCutAfterJust::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
