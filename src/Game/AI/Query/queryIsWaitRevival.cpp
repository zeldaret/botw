#include "Game/AI/Query/queryIsWaitRevival.h"
#include <evfl/Query.h>

namespace uking::query {

IsWaitRevival::IsWaitRevival(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsWaitRevival::~IsWaitRevival() = default;

// FIXME: implement
int IsWaitRevival::doQuery() {
    return -1;
}

void IsWaitRevival::loadParams(const evfl::QueryArg& arg) {}

void IsWaitRevival::loadParams() {}

}  // namespace uking::query
