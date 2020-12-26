#include "Game/AI/Action/actionElectricAttack.h"

namespace uking::action {

ElectricAttack::ElectricAttack(const InitArg& arg) : TimeredASPlay(arg) {}

ElectricAttack::~ElectricAttack() = default;

bool ElectricAttack::init_(sead::Heap* heap) {
    return TimeredASPlay::init_(heap);
}

void ElectricAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    TimeredASPlay::enter_(params);
}

void ElectricAttack::leave_() {
    TimeredASPlay::leave_();
}

void ElectricAttack::loadParams_() {
    TimeredASPlay::loadParams_();
    getStaticParam(&mVoltage_s, "Voltage");
    getStaticParam(&mMaxTimer_s, "MaxTimer");
    getStaticParam(&mMaxKeepTimer_s, "MaxKeepTimer");
    getStaticParam(&mHitAfterTime_s, "HitAfterTime");
    getStaticParam(&mElectricActorName_s, "ElectricActorName");
    getStaticParam(&mElectricActorKey_s, "ElectricActorKey");
}

void ElectricAttack::calc_() {
    TimeredASPlay::calc_();
}

}  // namespace uking::action
