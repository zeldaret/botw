#include "Game/AI/Query/queryCheckTimeType.h"
#include <evfl/Query.h>

namespace uking::query {

CheckTimeType::CheckTimeType(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckTimeType::~CheckTimeType() = default;

// FIXME: implement
int CheckTimeType::doQuery() {
    return -1;
}

void CheckTimeType::loadParams(const evfl::QueryArg& arg) {}

void CheckTimeType::loadParams() {}

}  // namespace uking::query
