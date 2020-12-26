#include "Game/AI/Action/actionMultiVacuumRotScaleTimeByDistWithTgt.h"

namespace uking::action {

MultiVacuumRotScaleTimeByDistWithTgt::MultiVacuumRotScaleTimeByDistWithTgt(const InitArg& arg)
    : MultiVacuumRotScaleTimeByDistWithTgtBase(arg) {}

MultiVacuumRotScaleTimeByDistWithTgt::~MultiVacuumRotScaleTimeByDistWithTgt() = default;

bool MultiVacuumRotScaleTimeByDistWithTgt::init_(sead::Heap* heap) {
    return MultiVacuumRotScaleTimeByDistWithTgtBase::init_(heap);
}

void MultiVacuumRotScaleTimeByDistWithTgt::enter_(ksys::act::ai::InlineParamPack* params) {
    MultiVacuumRotScaleTimeByDistWithTgtBase::enter_(params);
}

void MultiVacuumRotScaleTimeByDistWithTgt::leave_() {
    MultiVacuumRotScaleTimeByDistWithTgtBase::leave_();
}

void MultiVacuumRotScaleTimeByDistWithTgt::loadParams_() {
    MultiVacuumRotScaleTimeByDistWithTgtBase::loadParams_();
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void MultiVacuumRotScaleTimeByDistWithTgt::calc_() {
    MultiVacuumRotScaleTimeByDistWithTgtBase::calc_();
}

}  // namespace uking::action
