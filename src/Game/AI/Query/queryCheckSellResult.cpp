#include "Game/AI/Query/queryCheckSellResult.h"
#include <evfl/Query.h>

namespace uking::query {

CheckSellResult::CheckSellResult(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckSellResult::~CheckSellResult() = default;

// FIXME: implement
int CheckSellResult::doQuery() {
    return -1;
}

void CheckSellResult::loadParams(const evfl::QueryArg& arg) {}

void CheckSellResult::loadParams() {}

}  // namespace uking::query
