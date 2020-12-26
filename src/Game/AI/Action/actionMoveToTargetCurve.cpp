#include "Game/AI/Action/actionMoveToTargetCurve.h"

namespace uking::action {

MoveToTargetCurve::MoveToTargetCurve(const InitArg& arg) : MoveToTargetCurveBase(arg) {}

MoveToTargetCurve::~MoveToTargetCurve() = default;

bool MoveToTargetCurve::init_(sead::Heap* heap) {
    return MoveToTargetCurveBase::init_(heap);
}

void MoveToTargetCurve::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveToTargetCurveBase::enter_(params);
}

void MoveToTargetCurve::leave_() {
    MoveToTargetCurveBase::leave_();
}

void MoveToTargetCurve::loadParams_() {
    MoveToTargetCurveBase::loadParams_();
    getMapUnitParam(&mTargetPosition_m, "TargetPosition");
}

void MoveToTargetCurve::calc_() {
    MoveToTargetCurveBase::calc_();
}

}  // namespace uking::action
