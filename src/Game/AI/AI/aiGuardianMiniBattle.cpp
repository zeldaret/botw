#include "Game/AI/AI/aiGuardianMiniBattle.h"

namespace uking::ai {

GuardianMiniBattle::GuardianMiniBattle(const InitArg& arg) : EnemyBattle(arg) {}

GuardianMiniBattle::~GuardianMiniBattle() = default;

bool GuardianMiniBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void GuardianMiniBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void GuardianMiniBattle::leave_() {
    EnemyBattle::leave_();
}

void GuardianMiniBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mRootNodeName_s, "RootNodeName");
    getStaticParam(&mArm1NodeName_s, "Arm1NodeName");
    getStaticParam(&mArm2NodeName_s, "Arm2NodeName");
    getStaticParam(&mArm3NodeName_s, "Arm3NodeName");
    getStaticParam(&mASSlotRight_s, "ASSlotRight");
    getStaticParam(&mASSlotLeft_s, "ASSlotLeft");
    getStaticParam(&mASSlotBack_s, "ASSlotBack");
    getStaticParam(&mRollingInterval_s, "RollingInterval");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mIsIgnoreArmCondition_s, "IsIgnoreArmCondition");
    getStaticParam(&mTurnMoveTime_s, "TurnMoveTime");
    getStaticParam(&mTurnMovePer_s, "TurnMovePer");
    getStaticParam(&mTurnMoveStartDist_s, "TurnMoveStartDist");
    getStaticParam(&mCounterStartDamageCount_s, "CounterStartDamageCount");
    getStaticParam(&mCounterStartTime_s, "CounterStartTime");
    getStaticParam(&mCheckOnNoNavMesh_s, "CheckOnNoNavMesh");
    getAITreeVariable(&mDamagedCount_a, "DamagedCount");
}

}  // namespace uking::ai
