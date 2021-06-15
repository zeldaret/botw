#include "Game/AI/Query/queryCheckManufactResult.h"
#include <evfl/Query.h>

namespace uking::query {

CheckManufactResult::CheckManufactResult(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckManufactResult::~CheckManufactResult() = default;

// FIXME: implement
int CheckManufactResult::doQuery() {
    return -1;
}

void CheckManufactResult::loadParams(const evfl::QueryArg& arg) {}

void CheckManufactResult::loadParams() {}

}  // namespace uking::query
