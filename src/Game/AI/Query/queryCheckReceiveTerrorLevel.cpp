#include "Game/AI/Query/queryCheckReceiveTerrorLevel.h"
#include <evfl/Query.h>

namespace uking::query {

CheckReceiveTerrorLevel::CheckReceiveTerrorLevel(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckReceiveTerrorLevel::~CheckReceiveTerrorLevel() = default;

// FIXME: implement
int CheckReceiveTerrorLevel::doQuery() {
    return -1;
}

void CheckReceiveTerrorLevel::loadParams(const evfl::QueryArg& arg) {}

void CheckReceiveTerrorLevel::loadParams() {}

}  // namespace uking::query
