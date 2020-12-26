#include "Game/AI/Action/actionTackleMove.h"

namespace uking::action {

TackleMove::TackleMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TackleMove::~TackleMove() = default;

bool TackleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TackleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TackleMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void TackleMove::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFailAngle_s, "FailAngle");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void TackleMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
