#include "Game/AI/Query/queryCheckHorseDeadCause.h"
#include <evfl/Query.h>

namespace uking::query {

CheckHorseDeadCause::CheckHorseDeadCause(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckHorseDeadCause::~CheckHorseDeadCause() = default;

// FIXME: implement
int CheckHorseDeadCause::doQuery() {
    return -1;
}

void CheckHorseDeadCause::loadParams(const evfl::QueryArg& arg) {}

void CheckHorseDeadCause::loadParams() {}

}  // namespace uking::query
