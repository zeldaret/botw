#include "Game/AI/Query/queryCheckRankOfEnemyAttackedNPC.h"
#include <evfl/Query.h>

namespace uking::query {

CheckRankOfEnemyAttackedNPC::CheckRankOfEnemyAttackedNPC(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckRankOfEnemyAttackedNPC::~CheckRankOfEnemyAttackedNPC() = default;

// FIXME: implement
int CheckRankOfEnemyAttackedNPC::doQuery() {
    return -1;
}

void CheckRankOfEnemyAttackedNPC::loadParams(const evfl::QueryArg& arg) {}

void CheckRankOfEnemyAttackedNPC::loadParams() {}

}  // namespace uking::query
