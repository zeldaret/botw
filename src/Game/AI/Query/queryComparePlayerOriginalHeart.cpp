#include "Game/AI/Query/queryComparePlayerOriginalHeart.h"
#include <evfl/Query.h>

namespace uking::query {

ComparePlayerOriginalHeart::ComparePlayerOriginalHeart(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

ComparePlayerOriginalHeart::~ComparePlayerOriginalHeart() = default;

// FIXME: implement
int ComparePlayerOriginalHeart::doQuery() {
    return -1;
}

void ComparePlayerOriginalHeart::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Threshold");
}

void ComparePlayerOriginalHeart::loadParams() {
    getDynamicParam(&mThreshold, "Threshold");
}

}  // namespace uking::query
