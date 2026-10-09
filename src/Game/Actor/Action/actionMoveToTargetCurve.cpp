#include "Game/Actor/Action/actionMoveToTargetCurve.h"

namespace uking::action {

MoveToTargetCurve::MoveToTargetCurve(const InitArg& arg) : CurveMoveToTargetBase(arg) {}

MoveToTargetCurve::~MoveToTargetCurve() = default;

bool MoveToTargetCurve::init_(sead::Heap* heap) {
    return CurveMoveToTargetBase::init_(heap);
}

void MoveToTargetCurve::enter_(ksys::act::ai::InlineParamPack* params) {
    CurveMoveToTargetBase::enter_(params);
}

void MoveToTargetCurve::leave_() {
    CurveMoveToTargetBase::leave_();
}

void MoveToTargetCurve::loadParams_() {
    CurveMoveToTargetBase::loadParams_();
    getMapUnitParam(&mTargetPosition_m, "TargetPosition");
}

void MoveToTargetCurve::calc_() {
    CurveMoveToTargetBase::calc_();
}

}  // namespace uking::action
