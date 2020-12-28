#include "Game/AI/Action/actionPlayerRideJump.h"

namespace uking::action {

PlayerRideJump::PlayerRideJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerRideJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerRideJump::leave_() {
    PlayerAction::leave_();
}

void PlayerRideJump::loadParams_() {
    getStaticParam(&mRideOffsetPosY_s, "RideOffsetPosY");
    getStaticParam(&mRideOffsetPosXZ_s, "RideOffsetPosXZ");
    getStaticParam(&mRideJumpTime_s, "RideJumpTime");
}

void PlayerRideJump::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
