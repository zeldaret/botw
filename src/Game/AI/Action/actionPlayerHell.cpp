#include "Game/AI/Action/actionPlayerHell.h"

namespace uking::action {

PlayerHell::PlayerHell(const InitArg& arg) : PlayerAction(arg) {}

void PlayerHell::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerHell::leave_() {
    PlayerAction::leave_();
}

void PlayerHell::loadParams_() {
    getDynamicParam(&mIsNoDamage_d, "IsNoDamage");
}

void PlayerHell::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
