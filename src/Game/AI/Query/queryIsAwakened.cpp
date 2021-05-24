#include "Game/AI/Query/queryIsAwakened.h"
#include <evfl/Query.h>

namespace uking::query {

IsAwakened::IsAwakened(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsAwakened::~IsAwakened() = default;

// FIXME: implement
int IsAwakened::doQuery() {
    return -1;
}

void IsAwakened::loadParams(const evfl::QueryArg& arg) {}

void IsAwakened::loadParams() {}

}  // namespace uking::query
