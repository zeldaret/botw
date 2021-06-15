#include "Game/AI/Query/queryCheckAppPoint.h"
#include <evfl/Query.h>

namespace uking::query {

CheckAppPoint::CheckAppPoint(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckAppPoint::~CheckAppPoint() = default;

// FIXME: implement
int CheckAppPoint::doQuery() {
    return -1;
}

void CheckAppPoint::loadParams(const evfl::QueryArg& arg) {}

void CheckAppPoint::loadParams() {}

}  // namespace uking::query
