#include "Game/AI/AI/aiDashAndAttack.h"

namespace uking::ai {

DashAndAttack::DashAndAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DashAndAttack::~DashAndAttack() = default;

bool DashAndAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DashAndAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DashAndAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DashAndAttack::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mAttackFrame_s, "AttackFrame");
    getStaticParam(&mOffsetLR_s, "OffsetLR");
    getStaticParam(&mAttackRange_s, "AttackRange");
    getStaticParam(&mTiredAngle_s, "TiredAngle");
    getStaticParam(&mTargetSpeedClampMax_s, "TargetSpeedClampMax");
    getStaticParam(&mIsAbleSkipNear_s, "IsAbleSkipNear");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
}

}  // namespace uking::ai
