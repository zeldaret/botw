#include "Game/AI/Query/queryCheckPlayerTemperatureCondition.h"
#include <evfl/Query.h>

namespace uking::query {

CheckPlayerTemperatureCondition::CheckPlayerTemperatureCondition(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckPlayerTemperatureCondition::~CheckPlayerTemperatureCondition() = default;

// FIXME: implement
int CheckPlayerTemperatureCondition::doQuery() {
    return -1;
}

void CheckPlayerTemperatureCondition::loadParams(const evfl::QueryArg& arg) {}

void CheckPlayerTemperatureCondition::loadParams() {}

}  // namespace uking::query
