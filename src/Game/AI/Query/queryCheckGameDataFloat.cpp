#include "Game/AI/Query/queryCheckGameDataFloat.h"
#include <evfl/query.h>

namespace uking::query {

CheckGameDataFloat::CheckGameDataFloat(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckGameDataFloat::~CheckGameDataFloat() = default;

// FIXME: implement
int CheckGameDataFloat::doQuery() {
    return -1;
}

void CheckGameDataFloat::loadParams(const evfl::QueryArg& arg) {
    loadFloat(arg.param_accessor, "Value");
    loadString(arg.param_accessor, "GameDataFloatName");
    loadString(arg.param_accessor, "Operator");
}

void CheckGameDataFloat::loadParams() {
    getDynamicParam(&mValue, "Value");
    getDynamicParam(&mGameDataFloatName, "GameDataFloatName");
    getDynamicParam(&mOperator, "Operator");
}

}  // namespace uking::query
