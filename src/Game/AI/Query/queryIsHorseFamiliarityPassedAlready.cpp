#include "Game/AI/Query/queryIsHorseFamiliarityPassedAlready.h"
#include <evfl/Query.h>

namespace uking::query {

IsHorseFamiliarityPassedAlready::IsHorseFamiliarityPassedAlready(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

IsHorseFamiliarityPassedAlready::~IsHorseFamiliarityPassedAlready() = default;

// FIXME: implement
int IsHorseFamiliarityPassedAlready::doQuery() {
    return -1;
}

void IsHorseFamiliarityPassedAlready::loadParams(const evfl::QueryArg& arg) {}

void IsHorseFamiliarityPassedAlready::loadParams() {}

}  // namespace uking::query
