#include "Game/Actor/Action/actionCurveMoveToTargetBase.h"

namespace uking::action {

CurveMoveToTargetBase::CurveMoveToTargetBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CurveMoveToTargetBase::~CurveMoveToTargetBase() = default;

bool CurveMoveToTargetBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CurveMoveToTargetBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CurveMoveToTargetBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void CurveMoveToTargetBase::loadParams_() {
    getStaticParam(&mMaxHeight_s, "MaxHeight");
    getStaticParam(&mTimeScale_s, "TimeScale");
    getStaticParam(&mIsDebugDrawTargetPos_s, "IsDebugDrawTargetPos");
}

void CurveMoveToTargetBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
