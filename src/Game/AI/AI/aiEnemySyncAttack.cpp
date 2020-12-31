#include "Game/AI/AI/aiEnemySyncAttack.h"

namespace uking::ai {

EnemySyncAttack::EnemySyncAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemySyncAttack::~EnemySyncAttack() = default;

void EnemySyncAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemySyncAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemySyncAttack::loadParams_() {
    getStaticParam(&mNormalASSlot_s, "NormalASSlot");
    getStaticParam(&mAttackASSlot_s, "AttackASSlot");
    getStaticParam(&mJustAvoidCheckLength_s, "JustAvoidCheckLength");
    getStaticParam(&mJustAvoidCheckAngle_s, "JustAvoidCheckAngle");
    getStaticParam(&mRootNodeName_s, "RootNodeName");
    getStaticParam(&mAttackNodeName_s, "AttackNodeName");
    getStaticParam(&mAttackNodeNameWait_s, "AttackNodeNameWait");
    getStaticParam(&mAttackASName_s, "AttackASName");
    getStaticParam(&mAtNodeName_s, "AtNodeName");
    getStaticParam(&mAttackDistMin_s, "AttackDistMin");
    getStaticParam(&mAttackDistMax_s, "AttackDistMax");
    getStaticParam(&mAttackInterval_s, "AttackInterval");
    getStaticParam(&mAttackIntervalRand_s, "AttackIntervalRand");
}

}  // namespace uking::ai
