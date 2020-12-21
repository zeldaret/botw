#include "Game/AI/Query/queryCompareGameDataInt.h"
#include <evfl/query.h>

namespace uking::query {

CompareGameDataInt::CompareGameDataInt(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CompareGameDataInt::~CompareGameDataInt() = default;

// FIXME: implement
int CompareGameDataInt::doQuery() {
    return -1;
}

void CompareGameDataInt::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "GameDataIntName_A");
    loadString(arg.param_accessor, "GameDataIntName_B");
    loadString(arg.param_accessor, "Operator");
}

void CompareGameDataInt::loadParams() {
    getDynamicParam(&mGameDataIntName_A, "GameDataIntName_A");
    getDynamicParam(&mGameDataIntName_B, "GameDataIntName_B");
    getDynamicParam(&mOperator, "Operator");
}

}  // namespace uking::query
