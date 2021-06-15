#include "Game/AI/Query/queryCheckWeather.h"
#include <evfl/Query.h>

namespace uking::query {

CheckWeather::CheckWeather(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckWeather::~CheckWeather() = default;

// FIXME: implement
int CheckWeather::doQuery() {
    return -1;
}

void CheckWeather::loadParams(const evfl::QueryArg& arg) {}

void CheckWeather::loadParams() {}

}  // namespace uking::query
