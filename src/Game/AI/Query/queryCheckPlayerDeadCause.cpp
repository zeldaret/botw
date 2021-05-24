#include "Game/AI/Query/queryCheckPlayerDeadCause.h"
#include <evfl/Query.h>

namespace uking::query {

CheckPlayerDeadCause::CheckPlayerDeadCause(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPlayerDeadCause::~CheckPlayerDeadCause() = default;

// FIXME: implement
int CheckPlayerDeadCause::doQuery() {
    return -1;
}

void CheckPlayerDeadCause::loadParams(const evfl::QueryArg& arg) {}

void CheckPlayerDeadCause::loadParams() {}

}  // namespace uking::query
