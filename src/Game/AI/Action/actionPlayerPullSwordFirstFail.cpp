#include "Game/AI/Action/actionPlayerPullSwordFirstFail.h"

namespace uking::action {

PlayerPullSwordFirstFail::PlayerPullSwordFirstFail(const InitArg& arg) : PlayerAction(arg) {}

void PlayerPullSwordFirstFail::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerPullSwordFirstFail::leave_() {
    PlayerAction::leave_();
}

void PlayerPullSwordFirstFail::loadParams_() {
    getStaticParam(&mFirstFailureWait_s, "FirstFailureWait");
}

void PlayerPullSwordFirstFail::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
