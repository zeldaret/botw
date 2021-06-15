#include "Game/AI/Query/queryCheckHorseRegistered.h"
#include <evfl/Query.h>

namespace uking::query {

CheckHorseRegistered::CheckHorseRegistered(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckHorseRegistered::~CheckHorseRegistered() = default;

// FIXME: implement
int CheckHorseRegistered::doQuery() {
    return -1;
}

void CheckHorseRegistered::loadParams(const evfl::QueryArg& arg) {}

void CheckHorseRegistered::loadParams() {}

}  // namespace uking::query
