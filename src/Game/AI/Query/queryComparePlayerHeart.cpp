#include "Game/AI/Query/queryComparePlayerHeart.h"
#include <evfl/Query.h>

namespace uking::query {

ComparePlayerHeart::ComparePlayerHeart(const InitArg& arg) : ksys::act::ai::Query(arg) {}

ComparePlayerHeart::~ComparePlayerHeart() = default;

// FIXME: implement
int ComparePlayerHeart::doQuery() {
    return -1;
}

void ComparePlayerHeart::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Threshold");
}

void ComparePlayerHeart::loadParams() {
    getDynamicParam(&mThreshold, "Threshold");
}

}  // namespace uking::query
