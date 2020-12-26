#include "Game/AI/Action/actionElectricBlownOff.h"

namespace uking::action {

ElectricBlownOff::ElectricBlownOff(const InitArg& arg) : BlownOff(arg) {}

ElectricBlownOff::~ElectricBlownOff() = default;

bool ElectricBlownOff::init_(sead::Heap* heap) {
    return BlownOff::init_(heap);
}

void ElectricBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    BlownOff::enter_(params);
}

void ElectricBlownOff::leave_() {
    BlownOff::leave_();
}

void ElectricBlownOff::loadParams_() {
    BlownOff::loadParams_();
    getStaticParam(&mVoltage_s, "Voltage");
    getStaticParam(&mMaxTimer_s, "MaxTimer");
    getStaticParam(&mMaxKeepTimer_s, "MaxKeepTimer");
    getStaticParam(&mElectricActorName_s, "ElectricActorName");
    getStaticParam(&mElectricActorKey_s, "ElectricActorKey");
}

void ElectricBlownOff::calc_() {
    BlownOff::calc_();
}

}  // namespace uking::action
