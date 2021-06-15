#include "Game/AI/Query/queryCanMarkMapPin.h"
#include <evfl/Query.h>

namespace uking::query {

CanMarkMapPin::CanMarkMapPin(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CanMarkMapPin::~CanMarkMapPin() = default;

// FIXME: implement
int CanMarkMapPin::doQuery() {
    return -1;
}

void CanMarkMapPin::loadParams(const evfl::QueryArg& arg) {}

void CanMarkMapPin::loadParams() {}

}  // namespace uking::query
