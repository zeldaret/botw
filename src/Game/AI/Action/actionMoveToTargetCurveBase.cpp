#include "Game/AI/Action/actionMoveToTargetCurveBase.h"

namespace uking::action {

MoveToTargetCurveBase::MoveToTargetCurveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MoveToTargetCurveBase::~MoveToTargetCurveBase() = default;

bool MoveToTargetCurveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MoveToTargetCurveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MoveToTargetCurveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void MoveToTargetCurveBase::loadParams_() {
    getStaticParam(&mMaxHeight_s, "MaxHeight");
    getStaticParam(&mTimeScale_s, "TimeScale");
    getStaticParam(&mIsDebugDrawTargetPos_s, "IsDebugDrawTargetPos");
}

void MoveToTargetCurveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
