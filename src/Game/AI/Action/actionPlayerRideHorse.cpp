#include "Game/AI/Action/actionPlayerRideHorse.h"

namespace uking::action {

PlayerRideHorse::PlayerRideHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PlayerRideHorse::~PlayerRideHorse() = default;

bool PlayerRideHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerRideHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PlayerRideHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void PlayerRideHorse::loadParams_() {
    getStaticParam(&mAccelerateInputDelayGear0_s, "AccelerateInputDelayGear0");
    getStaticParam(&mAccelerateInputDelayGear1_s, "AccelerateInputDelayGear1");
    getStaticParam(&mAccelerateInputDelayGear2_s, "AccelerateInputDelayGear2");
    getStaticParam(&mAccelerateInputDelayGear3_s, "AccelerateInputDelayGear3");
    getStaticParam(&mAccelerateInputDelayGearTop_s, "AccelerateInputDelayGearTop");
    getStaticParam(&mAccInputIgnoreFramesGear0_s, "AccInputIgnoreFramesGear0");
    getStaticParam(&mAccInputIgnoreFramesGear1_s, "AccInputIgnoreFramesGear1");
    getStaticParam(&mAccInputIgnoreFramesGear2_s, "AccInputIgnoreFramesGear2");
    getStaticParam(&mAccInputIgnoreFramesGear3_s, "AccInputIgnoreFramesGear3");
    getStaticParam(&mAccInputIgnoreFramesGearTop_s, "AccInputIgnoreFramesGearTop");
    getStaticParam(&mDecelerateInputThreshold_s, "DecelerateInputThreshold");
    getStaticParam(&mStopInputFrames_s, "StopInputFrames");
    getStaticParam(&mAccelerateInputThreshold_s, "AccelerateInputThreshold");
    getStaticParam(&mMoveBackInputThreshold_s, "MoveBackInputThreshold");
    getStaticParam(&mStickXClampAtGear0_s, "StickXClampAtGear0");
    getStaticParam(&mTurnStickXInputThreshold_s, "TurnStickXInputThreshold");
    getStaticParam(&mConstraintBreakThreshold_s, "ConstraintBreakThreshold");
    getDynamicParam(&mHasToPlayRidingOnAS_d, "HasToPlayRidingOnAS");
}

void PlayerRideHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
