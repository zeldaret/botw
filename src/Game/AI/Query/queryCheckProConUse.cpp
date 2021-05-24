#include "Game/AI/Query/queryCheckProConUse.h"
#include <evfl/Query.h>

namespace uking::query {

CheckProConUse::CheckProConUse(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckProConUse::~CheckProConUse() = default;

// FIXME: implement
int CheckProConUse::doQuery() {
    return -1;
}

void CheckProConUse::loadParams(const evfl::QueryArg& arg) {}

void CheckProConUse::loadParams() {}

}  // namespace uking::query
