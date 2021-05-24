#include "Game/AI/Query/queryCheckDeadlyQuestEscapeTiming.h"
#include <evfl/Query.h>

namespace uking::query {

CheckDeadlyQuestEscapeTiming::CheckDeadlyQuestEscapeTiming(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckDeadlyQuestEscapeTiming::~CheckDeadlyQuestEscapeTiming() = default;

// FIXME: implement
int CheckDeadlyQuestEscapeTiming::doQuery() {
    return -1;
}

void CheckDeadlyQuestEscapeTiming::loadParams(const evfl::QueryArg& arg) {}

void CheckDeadlyQuestEscapeTiming::loadParams() {}

}  // namespace uking::query
