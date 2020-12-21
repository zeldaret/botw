#include "Game/AI/Query/queryCheckDuringBloodyMoon.h"
#include <evfl/query.h>

namespace uking::query {

CheckDuringBloodyMoon::CheckDuringBloodyMoon(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckDuringBloodyMoon::~CheckDuringBloodyMoon() = default;

// FIXME: implement
int CheckDuringBloodyMoon::doQuery() {
    return -1;
}

void CheckDuringBloodyMoon::loadParams(const evfl::QueryArg& arg) {}

void CheckDuringBloodyMoon::loadParams() {}

}  // namespace uking::query
