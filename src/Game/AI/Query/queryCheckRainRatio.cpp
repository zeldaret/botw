#include "Game/AI/Query/queryCheckRainRatio.h"
#include <evfl/Query.h>

namespace uking::query {

CheckRainRatio::CheckRainRatio(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckRainRatio::~CheckRainRatio() = default;

// FIXME: implement
int CheckRainRatio::doQuery() {
    return -1;
}

void CheckRainRatio::loadParams(const evfl::QueryArg& arg) {
    loadFloat(arg.param_accessor, "RainRatio");
}

void CheckRainRatio::loadParams() {
    getDynamicParam(&mRainRatio, "RainRatio");
}

}  // namespace uking::query
