#include "Game/AI/Query/queryIsRideHorse.h"
#include <evfl/Query.h>

namespace uking::query {

IsRideHorse::IsRideHorse(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsRideHorse::~IsRideHorse() = default;

// FIXME: implement
int IsRideHorse::doQuery() {
    return -1;
}

void IsRideHorse::loadParams(const evfl::QueryArg& arg) {}

void IsRideHorse::loadParams() {}

}  // namespace uking::query
