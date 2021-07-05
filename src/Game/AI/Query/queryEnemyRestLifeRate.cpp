#include "Game/AI/Query/queryEnemyRestLifeRate.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::query {

EnemyRestLifeRate::EnemyRestLifeRate(const InitArg& arg) : ksys::act::ai::Query(arg) {}

EnemyRestLifeRate::~EnemyRestLifeRate() = default;

int EnemyRestLifeRate::doQuery() {
    s32* life = mActor->getLife();
    float value;

    if (life != nullptr)
        value = *life;
    else
        value = 1.0f;

    return mActor->getMaxLife() * *mCheckRate <= value;
}

void EnemyRestLifeRate::loadParams(const evfl::QueryArg& arg) {
    loadFloat(arg.param_accessor, "CheckRate");
}

void EnemyRestLifeRate::loadParams() {
    getDynamicParam(&mCheckRate, "CheckRate");
}

}  // namespace uking::query
