#include "Game/AI/Action/actionFloatWait.h"

namespace uking::action {

FloatWait::FloatWait(const InitArg& arg) : WaterFloatBase(arg) {}

FloatWait::~FloatWait() = default;

bool FloatWait::init_(sead::Heap* heap) {
    return WaterFloatBase::init_(heap);
}

void FloatWait::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatBase::enter_(params);
}

void FloatWait::leave_() {
    WaterFloatBase::leave_();
}

void FloatWait::loadParams_() {
    WaterFloatBase::loadParams_();
    getStaticParam(&mWaterEffectSpeedRate_s, "WaterEffectSpeedRate");
    getStaticParam(&mASKeyName_s, "ASKeyName");
}

void FloatWait::calc_() {
    WaterFloatBase::calc_();
}

}  // namespace uking::action
