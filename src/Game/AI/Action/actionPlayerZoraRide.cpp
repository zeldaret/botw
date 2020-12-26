#include "Game/AI/Action/actionPlayerZoraRide.h"

namespace uking::action {

PlayerZoraRide::PlayerZoraRide(const InitArg& arg) : PlayerAction(arg) {}

PlayerZoraRide::~PlayerZoraRide() = default;

bool PlayerZoraRide::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerZoraRide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerZoraRide::leave_() {
    PlayerAction::leave_();
}

void PlayerZoraRide::loadParams_() {
    getStaticParam(&mLowerAngleWaitTime_s, "LowerAngleWaitTime");
    getStaticParam(&mAimAngleAddApplyAngle_s, "AimAngleAddApplyAngle");
    getStaticParam(&mAimAngleAdd_s, "AimAngleAdd");
    getStaticParam(&mAimAngleAddApplySpeed_s, "AimAngleAddApplySpeed");
}

void PlayerZoraRide::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
