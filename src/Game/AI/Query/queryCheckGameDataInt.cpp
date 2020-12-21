#include "Game/AI/Query/queryCheckGameDataInt.h"
#include <evfl/query.h>

namespace uking::query {

CheckGameDataInt::CheckGameDataInt(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckGameDataInt::~CheckGameDataInt() = default;

// FIXME: implement
int CheckGameDataInt::doQuery() {
    return -1;
}

void CheckGameDataInt::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Value");
    loadString(arg.param_accessor, "GameDataIntName");
    loadString(arg.param_accessor, "Operator");
}

void CheckGameDataInt::loadParams() {
    getDynamicParam(&mValue, "Value");
    getDynamicParam(&mGameDataIntName, "GameDataIntName");
    getDynamicParam(&mOperator, "Operator");
}

}  // namespace uking::query
