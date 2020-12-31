#include "Game/AI/AI/aiBreathAttackEnemyBattle.h"

namespace uking::ai {

BreathAttackEnemyBattle::BreathAttackEnemyBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BreathAttackEnemyBattle::~BreathAttackEnemyBattle() = default;

bool BreathAttackEnemyBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BreathAttackEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BreathAttackEnemyBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BreathAttackEnemyBattle::loadParams_() {
    getStaticParam(&mEnlargeTime_s, "EnlargeTime");
    getStaticParam(&mAttackAngle_s, "AttackAngle");
    getStaticParam(&mAttackRatio_s, "AttackRatio");
    getStaticParam(&mBreathSize_s, "BreathSize");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
    getStaticParam(&mGlobalNoAtkTime_s, "GlobalNoAtkTime");
    getStaticParam(&mIsEndAfterAttack_s, "IsEndAfterAttack");
    getStaticParam(&mIsDeleteBreath_s, "IsDeleteBreath");
    getStaticParam(&mBreathName_s, "BreathName");
    getStaticParam(&mIsUpdateNoticeState_s, "IsUpdateNoticeState");
}

}  // namespace uking::ai
