#include "Game/AI/Action/actionForkAddCalcScaleMapUnit.h"

namespace uking::action {

ForkAddCalcScaleMapUnit::ForkAddCalcScaleMapUnit(const InitArg& arg) : Fork(arg) {}

ForkAddCalcScaleMapUnit::~ForkAddCalcScaleMapUnit() = default;

bool ForkAddCalcScaleMapUnit::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkAddCalcScaleMapUnit::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkAddCalcScaleMapUnit::leave_() {
    Fork::leave_();
}

void ForkAddCalcScaleMapUnit::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mStartRate_s, "StartRate");
    getStaticParam(&mAddRate_s, "AddRate");
    getStaticParam(&mMinAddScaleRate_s, "MinAddScaleRate");
    getMapUnitParam(&mScaleTime_m, "ScaleTime");
}

void ForkAddCalcScaleMapUnit::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
