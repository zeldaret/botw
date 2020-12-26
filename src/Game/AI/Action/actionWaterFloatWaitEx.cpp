#include "Game/AI/Action/actionWaterFloatWaitEx.h"

namespace uking::action {

WaterFloatWaitEx::WaterFloatWaitEx(const InitArg& arg) : WaterFloatWait(arg) {}

WaterFloatWaitEx::~WaterFloatWaitEx() = default;

bool WaterFloatWaitEx::init_(sead::Heap* heap) {
    return WaterFloatWait::init_(heap);
}

void WaterFloatWaitEx::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatWait::enter_(params);
}

void WaterFloatWaitEx::leave_() {
    WaterFloatWait::leave_();
}

void WaterFloatWaitEx::loadParams_() {
    WaterFloatWait::loadParams_();
    getStaticParam(&mAdditionalPosReduceRatio_s, "AdditionalPosReduceRatio");
    getStaticParam(&mAdditionalAngleReduceRatio_s, "AdditionalAngleReduceRatio");
    getStaticParam(&mAdditionalVelocityMax_s, "AdditionalVelocityMax");
    getStaticParam(&mWaterEffectSpeedRate_s, "WaterEffectSpeedRate");
}

void WaterFloatWaitEx::calc_() {
    WaterFloatWait::calc_();
}

}  // namespace uking::action
