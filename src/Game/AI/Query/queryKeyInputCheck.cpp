#include "Game/AI/Query/queryKeyInputCheck.h"
#include <evfl/Query.h>

namespace uking::query {

KeyInputCheck::KeyInputCheck(const InitArg& arg) : ksys::act::ai::Query(arg) {}

KeyInputCheck::~KeyInputCheck() = default;

// FIXME: implement
int KeyInputCheck::doQuery() {
    return -1;
}

void KeyInputCheck::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "ValidInput");
}

void KeyInputCheck::loadParams() {
    getDynamicParam(&mValidInput, "ValidInput");
}

}  // namespace uking::query
