#include "Game/AI/Action/actionWaterFloatFreeze.h"

namespace uking::action {

WaterFloatFreeze::WaterFloatFreeze(const InitArg& arg) : WaterFloatImmobile(arg) {}

WaterFloatFreeze::~WaterFloatFreeze() = default;

void WaterFloatFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatImmobile::enter_(params);
}

void WaterFloatFreeze::leave_() {
    WaterFloatImmobile::leave_();
}

void WaterFloatFreeze::loadParams_() {
    WaterFloatImmobile::loadParams_();
    getAITreeVariable(&mIsKeepFreeze_a, "IsKeepFreeze");
}

void WaterFloatFreeze::calc_() {
    WaterFloatImmobile::calc_();
}

}  // namespace uking::action
