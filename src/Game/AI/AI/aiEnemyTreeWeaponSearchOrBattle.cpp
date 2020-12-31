#include "Game/AI/AI/aiEnemyTreeWeaponSearchOrBattle.h"

namespace uking::ai {

EnemyTreeWeaponSearchOrBattle::EnemyTreeWeaponSearchOrBattle(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

EnemyTreeWeaponSearchOrBattle::~EnemyTreeWeaponSearchOrBattle() = default;

bool EnemyTreeWeaponSearchOrBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyTreeWeaponSearchOrBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyTreeWeaponSearchOrBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyTreeWeaponSearchOrBattle::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSearchDist_s, "SearchDist");
    getStaticParam(&mNoSearchDist_s, "NoSearchDist");
}

}  // namespace uking::ai
