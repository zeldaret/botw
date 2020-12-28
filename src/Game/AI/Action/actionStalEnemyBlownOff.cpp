#include "Game/AI/Action/actionStalEnemyBlownOff.h"

namespace uking::action {

StalEnemyBlownOff::StalEnemyBlownOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StalEnemyBlownOff::~StalEnemyBlownOff() = default;

void StalEnemyBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void StalEnemyBlownOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void StalEnemyBlownOff::loadParams_() {
    getStaticParam(&mDownTimeBase_s, "DownTimeBase");
    getStaticParam(&mDownTimeRand_s, "DownTimeRand");
    getStaticParam(&mRecoverTimer_s, "RecoverTimer");
    getStaticParam(&mHeadShotSpeed_s, "HeadShotSpeed");
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
    getStaticParam(&mWeaponDropSpeedXZ_s, "WeaponDropSpeedXZ");
    getStaticParam(&mHeadSpeedRate_s, "HeadSpeedRate");
    getStaticParam(&mMinHeadSpeedY_s, "MinHeadSpeedY");
    getStaticParam(&mMinHeadSpeedXZ_s, "MinHeadSpeedXZ");
    getStaticParam(&mHeadShotUseAddVec_s, "HeadShotUseAddVec");
    getStaticParam(&mPosBaseRagdollRbName_s, "PosBaseRagdollRbName");
    getStaticParam(&mDisableBoneName_s, "DisableBoneName");
    getStaticParam(&mEnableConstraintName_s, "EnableConstraintName");
    getStaticParam(&mUseRagConName_s, "UseRagConName");
    getStaticParam(&mBlownOffASName_s, "BlownOffASName");
    getStaticParam(&mPreUniteASName_s, "PreUniteASName");
    getStaticParam(&mUniteASName_s, "UniteASName");
    getStaticParam(&mDieASName_s, "DieASName");
    getStaticParam(&mHeadRagdollRigidNames_s, "HeadRagdollRigidNames");
    getStaticParam(&mArmRagdollRigidNames_s, "ArmRagdollRigidNames");
    getStaticParam(&mDownBackCtrlOffset_s, "DownBackCtrlOffset");
    getStaticParam(&mDownFrontCtrlOffset_s, "DownFrontCtrlOffset");
    getStaticParam(&mHeadShotAddVec_s, "HeadShotAddVec");
    getStaticParam(&mHeadRotateOffset_s, "HeadRotateOffset");
}

void StalEnemyBlownOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
