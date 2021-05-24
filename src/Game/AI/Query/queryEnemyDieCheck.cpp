#include "Game/AI/Query/queryEnemyDieCheck.h"
#include <evfl/Query.h>

namespace uking::query {

EnemyDieCheck::EnemyDieCheck(const InitArg& arg) : ksys::act::ai::Query(arg) {}

EnemyDieCheck::~EnemyDieCheck() = default;

// FIXME: implement
int EnemyDieCheck::doQuery() {
    return -1;
}

void EnemyDieCheck::loadParams(const evfl::QueryArg& arg) {}

void EnemyDieCheck::loadParams() {}

}  // namespace uking::query
