#include "Game/AI/Query/queryIsEquippedEnableDye.h"
#include <evfl/Query.h>

namespace uking::query {

IsEquippedEnableDye::IsEquippedEnableDye(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsEquippedEnableDye::~IsEquippedEnableDye() = default;

// FIXME: implement
int IsEquippedEnableDye::doQuery() {
    return -1;
}

void IsEquippedEnableDye::loadParams(const evfl::QueryArg& arg) {}

void IsEquippedEnableDye::loadParams() {}

}  // namespace uking::query
