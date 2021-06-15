#include "Game/AI/Query/queryIsSoldOut.h"
#include <evfl/Query.h>

namespace uking::query {

IsSoldOut::IsSoldOut(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsSoldOut::~IsSoldOut() = default;

// FIXME: implement
int IsSoldOut::doQuery() {
    return -1;
}

void IsSoldOut::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "TableName");
}

void IsSoldOut::loadParams() {
    getDynamicParam(&mTableName, "TableName");
}

}  // namespace uking::query
