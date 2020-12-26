#include "Game/AI/Action/actionAnimalMoveBase.h"

namespace uking::action {

AnimalMoveBase::AnimalMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnimalMoveBase::~AnimalMoveBase() = default;

bool AnimalMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnimalMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AnimalMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnimalMoveBase::loadParams_() {
    getStaticParam(&mMinUseGear_s, "MinUseGear");
    getStaticParam(&mMaxUseGear_s, "MaxUseGear");
    getStaticParam(&mUseGearType_s, "UseGearType");
    getStaticParam(&mMinGearAtAutoGearDown_s, "MinGearAtAutoGearDown");
    getStaticParam(&mGoalDistanceTolerance_s, "GoalDistanceTolerance");
    getStaticParam(&mCanUseHorseGearInput_s, "CanUseHorseGearInput");
    getStaticParam(&mIsAutoGearDownEnabled_s, "IsAutoGearDownEnabled");
    getStaticParam(&mHasToDecelerateNearGoal_s, "HasToDecelerateNearGoal");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AnimalMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
