#include "Game/AI/Query/queryCheckPlayerRideHorse.h"
#include <evfl/Query.h>

namespace uking::query {

CheckPlayerRideHorse::CheckPlayerRideHorse(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPlayerRideHorse::~CheckPlayerRideHorse() = default;

// FIXME: implement
int CheckPlayerRideHorse::doQuery() {
    return -1;
}

void CheckPlayerRideHorse::loadParams(const evfl::QueryArg& arg) {}

void CheckPlayerRideHorse::loadParams() {}

}  // namespace uking::query
