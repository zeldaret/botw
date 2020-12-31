#include "Game/AI/AI/aiGuardianMiniRollingAttackMove.h"

namespace uking::ai {

GuardianMiniRollingAttackMove::GuardianMiniRollingAttackMove(const InitArg& arg)
    : EnemyRangeKeepMove(arg) {}

GuardianMiniRollingAttackMove::~GuardianMiniRollingAttackMove() = default;

bool GuardianMiniRollingAttackMove::init_(sead::Heap* heap) {
    return EnemyRangeKeepMove::init_(heap);
}

void GuardianMiniRollingAttackMove::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRangeKeepMove::enter_(params);
}

void GuardianMiniRollingAttackMove::leave_() {
    EnemyRangeKeepMove::leave_();
}

void GuardianMiniRollingAttackMove::loadParams_() {
    EnemyRangeKeepMove::loadParams_();
    getStaticParam(&mRootNodeName_s, "RootNodeName");
    getStaticParam(&mAttackNodeName_s, "AttackNodeName");
    getStaticParam(&mAttackASName_s, "AttackASName");
    getStaticParam(&mRollingNumMin_s, "RollingNumMin");
    getStaticParam(&mRollingNumMax_s, "RollingNumMax");
    getStaticParam(&mRollingWaitTime_s, "RollingWaitTime");
    getStaticParam(&mRollingIntervalTime_s, "RollingIntervalTime");
    getStaticParam(&mStopRollingNum_s, "StopRollingNum");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mBackWalkRotSpeedRatio_s, "BackWalkRotSpeedRatio");
    getStaticParam(&mRushRotSpeedRatio_s, "RushRotSpeedRatio");
    getStaticParam(&mAttackType_s, "AttackType");
    getStaticParam(&mBackWalkMinTime_s, "BackWalkMinTime");
    getStaticParam(&mBackWalkRollingStartTime_s, "BackWalkRollingStartTime");
    getStaticParam(&mBackWalkDist_s, "BackWalkDist");
    getStaticParam(&mRushAttackImpulse_s, "RushAttackImpulse");
    getStaticParam(&mRollingStopTime_s, "RollingStopTime");
    getStaticParam(&mIsValidChanceTime_s, "IsValidChanceTime");
    getStaticParam(&mCrashDamage_s, "CrashDamage");
    getStaticParam(&mBreakPillarTime_s, "BreakPillarTime");
}

}  // namespace uking::ai
