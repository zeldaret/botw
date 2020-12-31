#include "Game/AI/AI/aiNPCAttack.h"

namespace uking::ai {

NPCAttack::NPCAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCAttack::~NPCAttack() = default;

bool NPCAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCAttack::loadParams_() {
    getStaticParam(&mActionBaseTime_s, "ActionBaseTime");
    getStaticParam(&mActionTimePlay_s, "ActionTimePlay");
    getStaticParam(&mActionRate_s, "ActionRate");
    getStaticParam(&mAttackRate_s, "AttackRate");
    getStaticParam(&mAttackModeTime_s, "AttackModeTime");
    getStaticParam(&mGuardModeTime_s, "GuardModeTime");
    getStaticParam(&mEnemyChanceTime_s, "EnemyChanceTime");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mIsBattleStart_d, "IsBattleStart");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mEnemyLink_d, "EnemyLink");
}

}  // namespace uking::ai
