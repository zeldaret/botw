#include "Game/AI/Action/actionLastBossFlyWait.h"

namespace uking::action {

LastBossFlyWait::LastBossFlyWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossFlyWait::~LastBossFlyWait() = default;

bool LastBossFlyWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossFlyWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossFlyWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossFlyWait::loadParams_() {
    getStaticParam(&mDamageCounter_s, "DamageCounter");
    getStaticParam(&mAmplitude_s, "Amplitude");
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mMoveRate_s, "MoveRate");
    getStaticParam(&mEndTime_s, "EndTime");
    getStaticParam(&mEndTimeRandRange_s, "EndTimeRandRange");
    getStaticParam(&mBaseYOffset_s, "BaseYOffset");
    getStaticParam(&mIsChemicalOff_s, "IsChemicalOff");
    getStaticParam(&mWaitAS_s, "WaitAS");
    getDynamicParam(&mIsResetEndTime_d, "IsResetEndTime");
}

void LastBossFlyWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
