#include "Game/AI/AI/aiIceEnemyFeintBattle.h"

namespace uking::ai {

IceEnemyFeintBattle::IceEnemyFeintBattle(const InitArg& arg) : EnemyFeintBattle(arg) {}

IceEnemyFeintBattle::~IceEnemyFeintBattle() = default;

void IceEnemyFeintBattle::loadParams_() {
    EnemyFeintBattle::loadParams_();
}

}  // namespace uking::ai
