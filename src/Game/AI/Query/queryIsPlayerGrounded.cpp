#include "Game/AI/Query/queryIsPlayerGrounded.h"
#include <evfl/Query.h>

namespace uking::query {

IsPlayerGrounded::IsPlayerGrounded(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsPlayerGrounded::~IsPlayerGrounded() = default;

// FIXME: implement
int IsPlayerGrounded::doQuery() {
    return -1;
}

void IsPlayerGrounded::loadParams(const evfl::QueryArg& arg) {}

void IsPlayerGrounded::loadParams() {}

}  // namespace uking::query
