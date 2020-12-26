#include "Game/AI/Action/actionWaterUpDownMoveBase.h"

namespace uking::action {

WaterUpDownMoveBase::WaterUpDownMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaterUpDownMoveBase::~WaterUpDownMoveBase() = default;

bool WaterUpDownMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaterUpDownMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaterUpDownMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaterUpDownMoveBase::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mWaterFloatRadius_s, "WaterFloatRadius");
    getStaticParam(&mWaterFloatCycleTime_s, "WaterFloatCycleTime");
    getStaticParam(&mASName_s, "ASName");
}

void WaterUpDownMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
