#include "Game/AI/Query/queryCheckDeadHorseResistered.h"
#include <evfl/Query.h>

namespace uking::query {

CheckDeadHorseResistered::CheckDeadHorseResistered(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckDeadHorseResistered::~CheckDeadHorseResistered() = default;

// FIXME: implement
int CheckDeadHorseResistered::doQuery() {
    return -1;
}

void CheckDeadHorseResistered::loadParams(const evfl::QueryArg& arg) {}

void CheckDeadHorseResistered::loadParams() {}

}  // namespace uking::query
