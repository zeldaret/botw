#include "Game/AI/Query/queryCheckGiveReward.h"
#include <evfl/Query.h>

namespace uking::query {

CheckGiveReward::CheckGiveReward(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckGiveReward::~CheckGiveReward() = default;

int CheckGiveReward::doQuery() {
    return 0;
}

}  // namespace uking::query
