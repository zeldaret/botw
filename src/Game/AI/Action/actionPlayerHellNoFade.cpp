#include "Game/AI/Action/actionPlayerHellNoFade.h"

namespace uking::action {

PlayerHellNoFade::PlayerHellNoFade(const InitArg& arg) : PlayerAction(arg) {}

void PlayerHellNoFade::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerHellNoFade::leave_() {
    PlayerAction::leave_();
}

void PlayerHellNoFade::loadParams_() {
    getStaticParam(&mCleaningTime_s, "CleaningTime");
}

void PlayerHellNoFade::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
