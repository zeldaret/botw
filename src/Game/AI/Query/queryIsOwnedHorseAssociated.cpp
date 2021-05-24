#include "Game/AI/Query/queryIsOwnedHorseAssociated.h"
#include <evfl/Query.h>

namespace uking::query {

IsOwnedHorseAssociated::IsOwnedHorseAssociated(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsOwnedHorseAssociated::~IsOwnedHorseAssociated() = default;

// FIXME: implement
int IsOwnedHorseAssociated::doQuery() {
    return -1;
}

void IsOwnedHorseAssociated::loadParams(const evfl::QueryArg& arg) {
    loadBool(arg.param_accessor, "IsRidden");
}

void IsOwnedHorseAssociated::loadParams() {
    getDynamicParam(&mIsRidden, "IsRidden");
}

}  // namespace uking::query
