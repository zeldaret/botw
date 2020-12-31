#include "Game/AI/AI/aiAssassinBossFirstBattle.h"

namespace uking::ai {

AssassinBossFirstBattle::AssassinBossFirstBattle(const InitArg& arg) : EnemyBattle(arg) {}

AssassinBossFirstBattle::~AssassinBossFirstBattle() = default;

bool AssassinBossFirstBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void AssassinBossFirstBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void AssassinBossFirstBattle::leave_() {
    EnemyBattle::leave_();
}

void AssassinBossFirstBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mIronBallNum_s, "IronBallNum");
    getStaticParam(&mIronBallKeyName_s, "IronBallKeyName");
    getStaticParam(&mGuardAngle_s, "GuardAngle");
    getStaticParam(&mAttackInterseptDist_s, "AttackInterseptDist");
}

}  // namespace uking::ai
