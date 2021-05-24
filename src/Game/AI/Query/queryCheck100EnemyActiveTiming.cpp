#include "Game/AI/Query/queryCheck100EnemyActiveTiming.h"
#include <evfl/Query.h>

namespace uking::query {

Check100EnemyActiveTiming::Check100EnemyActiveTiming(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

Check100EnemyActiveTiming::~Check100EnemyActiveTiming() = default;

// FIXME: implement
int Check100EnemyActiveTiming::doQuery() {
    return -1;
}

void Check100EnemyActiveTiming::loadParams(const evfl::QueryArg& arg) {}

void Check100EnemyActiveTiming::loadParams() {}

}  // namespace uking::query
