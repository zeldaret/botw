#include "Game/AI/Action/actionWaterFloatElectricParalysis.h"

namespace uking::action {

WaterFloatElectricParalysis::WaterFloatElectricParalysis(const InitArg& arg)
    : OneTimeWaterFloatStopASPlay(arg) {}

WaterFloatElectricParalysis::~WaterFloatElectricParalysis() = default;

bool WaterFloatElectricParalysis::init_(sead::Heap* heap) {
    return OneTimeWaterFloatStopASPlay::init_(heap);
}

void WaterFloatElectricParalysis::enter_(ksys::act::ai::InlineParamPack* params) {
    OneTimeWaterFloatStopASPlay::enter_(params);
}

void WaterFloatElectricParalysis::leave_() {
    OneTimeWaterFloatStopASPlay::leave_();
}

void WaterFloatElectricParalysis::loadParams_() {
    OneTimeWaterFloatStopASPlay::loadParams_();
}

void WaterFloatElectricParalysis::calc_() {
    OneTimeWaterFloatStopASPlay::calc_();
}

}  // namespace uking::action
