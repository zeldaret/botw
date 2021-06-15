#include "Game/AI/Query/queryComparePlayerMaxStamina.h"
#include <evfl/Query.h>

namespace uking::query {

ComparePlayerMaxStamina::ComparePlayerMaxStamina(const InitArg& arg) : ksys::act::ai::Query(arg) {}

ComparePlayerMaxStamina::~ComparePlayerMaxStamina() = default;

// FIXME: implement
int ComparePlayerMaxStamina::doQuery() {
    return -1;
}

void ComparePlayerMaxStamina::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Threshold");
}

void ComparePlayerMaxStamina::loadParams() {
    getDynamicParam(&mThreshold, "Threshold");
}

}  // namespace uking::query
