#include "Game/AI/Action/actionWaterFloatElectricParalysis.h"

namespace uking::action {

WaterFloatElectricParalysis::WaterFloatElectricParalysis(const InitArg& arg)
    : OneTimeWaterFloatStopASPlay(arg) {}

WaterFloatElectricParalysis::~WaterFloatElectricParalysis() = default;

void WaterFloatElectricParalysis::loadParams_() {
    OneTimeWaterFloatStopASPlay::loadParams_();
}

void WaterFloatElectricParalysis::calc_() {
    OneTimeWaterFloatStopASPlay::calc_();
}

}  // namespace uking::action
