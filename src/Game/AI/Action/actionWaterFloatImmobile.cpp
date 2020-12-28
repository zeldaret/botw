#include "Game/AI/Action/actionWaterFloatImmobile.h"

namespace uking::action {

WaterFloatImmobile::WaterFloatImmobile(const InitArg& arg) : WaterFloatBase(arg) {}

bool WaterFloatImmobile::init_(sead::Heap* heap) {
    return WaterFloatBase::init_(heap);
}

void WaterFloatImmobile::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatBase::enter_(params);
}

void WaterFloatImmobile::leave_() {
    WaterFloatBase::leave_();
}

void WaterFloatImmobile::loadParams_() {
    WaterFloatBase::loadParams_();
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngleReduceRatio_s, "AngleReduceRatio");
}

void WaterFloatImmobile::calc_() {
    WaterFloatBase::calc_();
}

}  // namespace uking::action
