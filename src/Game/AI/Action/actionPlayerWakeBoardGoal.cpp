#include "Game/AI/Action/actionPlayerWakeBoardGoal.h"

namespace uking::action {

PlayerWakeBoardGoal::PlayerWakeBoardGoal(const InitArg& arg) : PlayerAction(arg) {}

PlayerWakeBoardGoal::~PlayerWakeBoardGoal() = default;

void PlayerWakeBoardGoal::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWakeBoardGoal::leave_() {
    PlayerAction::leave_();
}

void PlayerWakeBoardGoal::loadParams_() {
    getDynamicParam(&mASName_d, "ASName");
}

void PlayerWakeBoardGoal::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
