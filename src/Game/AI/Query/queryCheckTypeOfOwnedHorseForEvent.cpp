#include "Game/AI/Query/queryCheckTypeOfOwnedHorseForEvent.h"
#include <evfl/Query.h>

namespace uking::query {

CheckTypeOfOwnedHorseForEvent::CheckTypeOfOwnedHorseForEvent(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckTypeOfOwnedHorseForEvent::~CheckTypeOfOwnedHorseForEvent() = default;

// FIXME: implement
int CheckTypeOfOwnedHorseForEvent::doQuery() {
    return -1;
}

void CheckTypeOfOwnedHorseForEvent::loadParams(const evfl::QueryArg& arg) {}

void CheckTypeOfOwnedHorseForEvent::loadParams() {}

}  // namespace uking::query
