#include "Game/AI/Action/actionWaterFloatBase.h"

namespace uking::action {

WaterFloatBase::WaterFloatBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaterFloatBase::~WaterFloatBase() = default;

bool WaterFloatBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaterFloatBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaterFloatBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaterFloatBase::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatRadius_s, "FloatRadius");
    getStaticParam(&mFloatCycleTime_s, "FloatCycleTime");
    getStaticParam(&mChangeDepthSpeed_s, "ChangeDepthSpeed");
    getStaticParam(&mIsCheckWaterFall_s, "IsCheckWaterFall");
}

void WaterFloatBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
