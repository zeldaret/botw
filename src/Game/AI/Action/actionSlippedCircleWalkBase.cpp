#include "Game/AI/Action/actionSlippedCircleWalkBase.h"

namespace uking::action {

SlippedCircleWalkBase::SlippedCircleWalkBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SlippedCircleWalkBase::~SlippedCircleWalkBase() = default;

bool SlippedCircleWalkBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SlippedCircleWalkBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SlippedCircleWalkBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void SlippedCircleWalkBase::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mRotDist_s, "RotDist");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getDynamicParam(&mRotDir_d, "RotDir");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SlippedCircleWalkBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
