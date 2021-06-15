#include "Game/AI/Query/queryComparePlayerMaxHeart.h"
#include <evfl/Query.h>

namespace uking::query {

ComparePlayerMaxHeart::ComparePlayerMaxHeart(const InitArg& arg) : ksys::act::ai::Query(arg) {}

ComparePlayerMaxHeart::~ComparePlayerMaxHeart() = default;

// FIXME: implement
int ComparePlayerMaxHeart::doQuery() {
    return -1;
}

void ComparePlayerMaxHeart::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Threshold");
}

void ComparePlayerMaxHeart::loadParams() {
    getDynamicParam(&mThreshold, "Threshold");
}

}  // namespace uking::query
