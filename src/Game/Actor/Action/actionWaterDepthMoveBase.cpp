#include "Game/Actor/Action/actionWaterDepthMoveBase.h"

namespace uking::action {

WaterDepthMoveBase::WaterDepthMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaterDepthMoveBase::~WaterDepthMoveBase() = default;

bool WaterDepthMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaterDepthMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaterDepthMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaterDepthMoveBase::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mWaterFloatRadius_s, "WaterFloatRadius");
    getStaticParam(&mWaterFloatCycleTime_s, "WaterFloatCycleTime");
    getStaticParam(&mASName_s, "ASName");
}

void WaterDepthMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
