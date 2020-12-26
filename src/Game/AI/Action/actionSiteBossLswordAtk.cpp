#include "Game/AI/Action/actionSiteBossLswordAtk.h"

namespace uking::action {

SiteBossLswordAtk::SiteBossLswordAtk(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossLswordAtk::~SiteBossLswordAtk() = default;

bool SiteBossLswordAtk::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossLswordAtk::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossLswordAtk::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossLswordAtk::loadParams_() {
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mNearMoveSpeed_s, "NearMoveSpeed");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mFarMoveSpeed_s, "FarMoveSpeed");
    getStaticParam(&mIsIgnoreCancelAttack_s, "IsIgnoreCancelAttack");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SiteBossLswordAtk::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
