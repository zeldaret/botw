#include "Game/AI/AI/aiEnemyShieldSearchOrBattle.h"

namespace uking::ai {

EnemyShieldSearchOrBattle::EnemyShieldSearchOrBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyShieldSearchOrBattle::~EnemyShieldSearchOrBattle() = default;

bool EnemyShieldSearchOrBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyShieldSearchOrBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyShieldSearchOrBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyShieldSearchOrBattle::loadParams_() {
    getStaticParam(&mShieldIdx_s, "ShieldIdx");
    getStaticParam(&mSearchShieldDist_s, "SearchShieldDist");
    getStaticParam(&mNoShieldSearchDist_s, "NoShieldSearchDist");
    getStaticParam(&mNoShieldTargetNearDist_s, "NoShieldTargetNearDist");
    getStaticParam(&mShieldReachDist_s, "ShieldReachDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mNoShieldEquipWpIdx_s, "NoShieldEquipWpIdx");
}

}  // namespace uking::ai
