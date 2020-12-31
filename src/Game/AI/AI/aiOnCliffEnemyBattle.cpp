#include "Game/AI/AI/aiOnCliffEnemyBattle.h"

namespace uking::ai {

OnCliffEnemyBattle::OnCliffEnemyBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OnCliffEnemyBattle::~OnCliffEnemyBattle() = default;

bool OnCliffEnemyBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OnCliffEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void OnCliffEnemyBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OnCliffEnemyBattle::loadParams_() {
    getStaticParam(&mLostCounter_s, "LostCounter");
    getStaticParam(&mAttackDist_s, "AttackDist");
    getStaticParam(&mAttackAngleH_s, "AttackAngleH");
    getStaticParam(&mAttackAngleVMax_s, "AttackAngleVMax");
    getStaticParam(&mAttackAngleVMin_s, "AttackAngleVMin");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
}

}  // namespace uking::ai
