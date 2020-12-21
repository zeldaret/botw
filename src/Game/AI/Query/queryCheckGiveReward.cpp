#include "Game/AI/Query/queryCheckGiveReward.h"
#include <evfl/query.h>

namespace uking::query {

CheckGiveReward::CheckGiveReward(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckGiveReward::~CheckGiveReward() = default;

// FIXME: implement
int CheckGiveReward::doQuery() {
    return -1;
}

void CheckGiveReward::loadParams(const evfl::QueryArg& arg) {}

void CheckGiveReward::loadParams() {}

}  // namespace uking::query
