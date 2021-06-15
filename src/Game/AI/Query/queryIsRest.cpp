#include "Game/AI/Query/queryIsRest.h"
#include <evfl/Query.h>

namespace uking::query {

IsRest::IsRest(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsRest::~IsRest() = default;

// FIXME: implement
int IsRest::doQuery() {
    return -1;
}

void IsRest::loadParams(const evfl::QueryArg& arg) {}

void IsRest::loadParams() {}

}  // namespace uking::query
