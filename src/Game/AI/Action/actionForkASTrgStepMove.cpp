#include "Game/AI/Action/actionForkASTrgStepMove.h"

namespace uking::action {

ForkASTrgStepMove::ForkASTrgStepMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgStepMove::~ForkASTrgStepMove() = default;

bool ForkASTrgStepMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgStepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkASTrgStepMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgStepMove::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCloseDist_s, "CloseDist");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinishDist_s, "FinishDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkASTrgStepMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
