#include "Game/Actor/Action/actionSlippedCircleMoveBase.h"

namespace uking::action {

SlippedCircleMoveBase::SlippedCircleMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SlippedCircleMoveBase::~SlippedCircleMoveBase() = default;

bool SlippedCircleMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SlippedCircleMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SlippedCircleMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void SlippedCircleMoveBase::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mRotDist_s, "RotDist");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getDynamicParam(&mRotDir_d, "RotDir");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SlippedCircleMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
