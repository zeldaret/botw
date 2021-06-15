#include "Game/AI/Query/queryCheckBalladOfHeroActiveTiming.h"
#include <evfl/Query.h>

namespace uking::query {

CheckBalladOfHeroActiveTiming::CheckBalladOfHeroActiveTiming(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckBalladOfHeroActiveTiming::~CheckBalladOfHeroActiveTiming() = default;

// FIXME: implement
int CheckBalladOfHeroActiveTiming::doQuery() {
    return -1;
}

void CheckBalladOfHeroActiveTiming::loadParams(const evfl::QueryArg& arg) {}

void CheckBalladOfHeroActiveTiming::loadParams() {}

}  // namespace uking::query
