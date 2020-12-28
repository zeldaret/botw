#include "Game/AI/Action/actionAnimalMoveGuidedBase.h"

namespace uking::action {

AnimalMoveGuidedBase::AnimalMoveGuidedBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool AnimalMoveGuidedBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnimalMoveGuidedBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AnimalMoveGuidedBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnimalMoveGuidedBase::loadParams_() {
    getStaticParam(&mMinUseGear_s, "MinUseGear");
    getStaticParam(&mMaxUseGear_s, "MaxUseGear");
    getStaticParam(&mUseGearType_s, "UseGearType");
    getStaticParam(&mAutoStopAndTurnMode_s, "AutoStopAndTurnMode");
    getStaticParam(&mMinGearAtAutoGearDown_s, "MinGearAtAutoGearDown");
    getStaticParam(&mGoalDistanceTolerance_s, "GoalDistanceTolerance");
    getStaticParam(&mCanUseHorseGearInput_s, "CanUseHorseGearInput");
    getStaticParam(&mIsAutoGearDownEnabled_s, "IsAutoGearDownEnabled");
    getStaticParam(&mHasToDecelerateNearGoal_s, "HasToDecelerateNearGoal");
    getStaticParam(&mWaitUntilPathSucceeded_s, "WaitUntilPathSucceeded");
}

void AnimalMoveGuidedBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
