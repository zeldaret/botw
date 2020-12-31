#include "Game/AI/AI/aiEnemyFeintBattle.h"

namespace uking::ai {

EnemyFeintBattle::EnemyFeintBattle(const InitArg& arg) : EnemyBattle(arg) {}

EnemyFeintBattle::~EnemyFeintBattle() = default;

void EnemyFeintBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mIsAttackEnd_s, "IsAttackEnd");
}

}  // namespace uking::ai
