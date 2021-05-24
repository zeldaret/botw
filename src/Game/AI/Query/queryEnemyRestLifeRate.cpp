#include "Game/AI/Query/queryEnemyRestLifeRate.h"
#include <evfl/Query.h>

namespace uking::query {

EnemyRestLifeRate::EnemyRestLifeRate(const InitArg& arg) : ksys::act::ai::Query(arg) {}

EnemyRestLifeRate::~EnemyRestLifeRate() = default;

// FIXME: implement
int EnemyRestLifeRate::doQuery() {
    return -1;
}

void EnemyRestLifeRate::loadParams(const evfl::QueryArg& arg) {
    loadFloat(arg.param_accessor, "CheckRate");
}

void EnemyRestLifeRate::loadParams() {
    getDynamicParam(&mCheckRate, "CheckRate");
}

}  // namespace uking::query
