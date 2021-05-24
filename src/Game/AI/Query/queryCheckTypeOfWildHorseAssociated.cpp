#include "Game/AI/Query/queryCheckTypeOfWildHorseAssociated.h"
#include <evfl/Query.h>

namespace uking::query {

CheckTypeOfWildHorseAssociated::CheckTypeOfWildHorseAssociated(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckTypeOfWildHorseAssociated::~CheckTypeOfWildHorseAssociated() = default;

// FIXME: implement
int CheckTypeOfWildHorseAssociated::doQuery() {
    return -1;
}

void CheckTypeOfWildHorseAssociated::loadParams(const evfl::QueryArg& arg) {}

void CheckTypeOfWildHorseAssociated::loadParams() {}

}  // namespace uking::query
