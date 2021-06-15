#include "Game/AI/Query/queryCheckLastDamageAttacker.h"
#include <evfl/Query.h>

namespace uking::query {

CheckLastDamageAttacker::CheckLastDamageAttacker(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckLastDamageAttacker::~CheckLastDamageAttacker() = default;

// FIXME: implement
int CheckLastDamageAttacker::doQuery() {
    return -1;
}

void CheckLastDamageAttacker::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "Name");
}

void CheckLastDamageAttacker::loadParams() {
    getDynamicParam(&mName, "Name");
}

}  // namespace uking::query
