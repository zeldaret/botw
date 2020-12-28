#include "Game/AI/Action/actionPlayerDiveMove.h"

namespace uking::action {

PlayerDiveMove::PlayerDiveMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDiveMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDiveMove::leave_() {
    PlayerAction::leave_();
}

void PlayerDiveMove::loadParams_() {
    getStaticParam(&mAnmDrivenDist_s, "AnmDrivenDist");
    getStaticParam(&mFinishDist_s, "FinishDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void PlayerDiveMove::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
