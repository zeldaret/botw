#include "Game/AI/Query/queryCheckTerrorLevel.h"
#include <evfl/Query.h>

namespace uking::query {

CheckTerrorLevel::CheckTerrorLevel(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckTerrorLevel::~CheckTerrorLevel() = default;

// FIXME: implement
int CheckTerrorLevel::doQuery() {
    return -1;
}

void CheckTerrorLevel::loadParams(const evfl::QueryArg& arg) {}

void CheckTerrorLevel::loadParams() {}

}  // namespace uking::query
