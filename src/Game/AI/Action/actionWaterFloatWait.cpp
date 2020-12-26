#include "Game/AI/Action/actionWaterFloatWait.h"

namespace uking::action {

WaterFloatWait::WaterFloatWait(const InitArg& arg) : WaterFloatImmobile(arg) {}

WaterFloatWait::~WaterFloatWait() = default;

bool WaterFloatWait::init_(sead::Heap* heap) {
    return WaterFloatImmobile::init_(heap);
}

void WaterFloatWait::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatImmobile::enter_(params);
}

void WaterFloatWait::leave_() {
    WaterFloatImmobile::leave_();
}

void WaterFloatWait::loadParams_() {
    WaterFloatImmobile::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mIsEndWhenASFinished_s, "IsEndWhenASFinished");
    getStaticParam(&mASName_s, "ASName");
}

void WaterFloatWait::calc_() {
    WaterFloatImmobile::calc_();
}

}  // namespace uking::action
