#include "Game/AI/Action/actionPlayerCutDash.h"

namespace uking::action {

PlayerCutDash::PlayerCutDash(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutDash::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutDash::leave_() {
    PlayerAction::leave_();
}

void PlayerCutDash::loadParams_() {
    getStaticParam(&mSearchAngle_s, "SearchAngle");
}

void PlayerCutDash::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
