#include "Game/AI/Query/queryCompareGameDataFloat.h"
#include <evfl/query.h>

namespace uking::query {

CompareGameDataFloat::CompareGameDataFloat(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CompareGameDataFloat::~CompareGameDataFloat() = default;

// FIXME: implement
int CompareGameDataFloat::doQuery() {
    return -1;
}

void CompareGameDataFloat::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "GameDataFloatName_A");
    loadString(arg.param_accessor, "GameDataFloatName_B");
    loadString(arg.param_accessor, "Operator");
}

void CompareGameDataFloat::loadParams() {
    getDynamicParam(&mGameDataFloatName_A, "GameDataFloatName_A");
    getDynamicParam(&mGameDataFloatName_B, "GameDataFloatName_B");
    getDynamicParam(&mOperator, "Operator");
}

}  // namespace uking::query
