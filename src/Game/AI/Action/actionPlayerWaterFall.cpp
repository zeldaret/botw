#include "Game/AI/Action/actionPlayerWaterFall.h"

namespace uking::action {

PlayerWaterFall::PlayerWaterFall(const InitArg& arg) : PlayerAction(arg) {}

PlayerWaterFall::~PlayerWaterFall() = default;

void PlayerWaterFall::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWaterFall::leave_() {
    PlayerAction::leave_();
}

void PlayerWaterFall::loadParams_() {
    getStaticParam(&mSpeedClimb_s, "SpeedClimb");
    getDynamicParam(&mRailPtr_d, "RailPtr");
    getDynamicParam(&mFrontDir_d, "FrontDir");
}

void PlayerWaterFall::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
