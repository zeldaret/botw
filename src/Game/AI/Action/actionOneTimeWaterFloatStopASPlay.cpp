#include "Game/AI/Action/actionOneTimeWaterFloatStopASPlay.h"

namespace uking::action {

OneTimeWaterFloatStopASPlay::OneTimeWaterFloatStopASPlay(const InitArg& arg)
    : WaterFloatImmobile(arg) {}

OneTimeWaterFloatStopASPlay::~OneTimeWaterFloatStopASPlay() = default;

bool OneTimeWaterFloatStopASPlay::init_(sead::Heap* heap) {
    return WaterFloatImmobile::init_(heap);
}

void OneTimeWaterFloatStopASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatImmobile::enter_(params);
}

void OneTimeWaterFloatStopASPlay::leave_() {
    WaterFloatImmobile::leave_();
}

void OneTimeWaterFloatStopASPlay::loadParams_() {
    WaterFloatImmobile::loadParams_();
    getStaticParam(&mIgnoreSameAS_s, "IgnoreSameAS");
    getStaticParam(&mASName_s, "ASName");
}

void OneTimeWaterFloatStopASPlay::calc_() {
    WaterFloatImmobile::calc_();
}

}  // namespace uking::action
