#include "Game/Actor/Action/actionMultiVacuumRotBase.h"

namespace uking::action {

MultiVacuumRotBase::MultiVacuumRotBase(const InitArg& arg) : MultiVacuumBase(arg) {}

MultiVacuumRotBase::~MultiVacuumRotBase() = default;

bool MultiVacuumRotBase::init_(sead::Heap* heap) {
    return MultiVacuumBase::init_(heap);
}

void MultiVacuumRotBase::enter_(ksys::act::ai::InlineParamPack* params) {
    MultiVacuumBase::enter_(params);
}

void MultiVacuumRotBase::leave_() {
    MultiVacuumBase::leave_();
}

void MultiVacuumRotBase::loadParams_() {
    MultiVacuumBase::loadParams_();
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void MultiVacuumRotBase::calc_() {
    MultiVacuumBase::calc_();
}

}  // namespace uking::action
