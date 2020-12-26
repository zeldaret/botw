#include "Game/AI/Action/actionLinearFlyAttackBase.h"

namespace uking::action {

LinearFlyAttackBase::LinearFlyAttackBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LinearFlyAttackBase::~LinearFlyAttackBase() = default;

bool LinearFlyAttackBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LinearFlyAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LinearFlyAttackBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void LinearFlyAttackBase::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mAttackSpeed_s, "AttackSpeed");
    getStaticParam(&mAttackSlowDownRatio_s, "AttackSlowDownRatio");
    getStaticParam(&mTargetHeightOffset_s, "TargetHeightOffset");
    getStaticParam(&mThroughDist_s, "ThroughDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LinearFlyAttackBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
