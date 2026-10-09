#include "Game/Actor/Action/actionChemicalward.h"

namespace uking::action {

Chemicalward::Chemicalward(const InitArg& arg) : StopBase(arg) {}

Chemicalward::~Chemicalward() = default;

bool Chemicalward::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void Chemicalward::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void Chemicalward::leave_() {
    StopBase::leave_();
}

void Chemicalward::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mNodeAxisIdx_s, "NodeAxisIdx");
    getStaticParam(&mStableTime_s, "StableTime");
    getStaticParam(&mKeepTime_s, "KeepTime");
    getStaticParam(&mTiredTime_s, "TiredTime");
    getStaticParam(&mTiredRadius_s, "TiredRadius");
    getStaticParam(&mTiredAngle_s, "TiredAngle");
    getStaticParam(&mVoltage_s, "Voltage");
    getStaticParam(&mNodeName_s, "NodeName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void Chemicalward::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
