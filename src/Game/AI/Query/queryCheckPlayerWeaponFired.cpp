#include "Game/AI/Query/queryCheckPlayerWeaponFired.h"
#include <evfl/Query.h>

namespace uking::query {

CheckPlayerWeaponFired::CheckPlayerWeaponFired(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPlayerWeaponFired::~CheckPlayerWeaponFired() = default;

// FIXME: implement
int CheckPlayerWeaponFired::doQuery() {
    return -1;
}

void CheckPlayerWeaponFired::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "CheckFireType");
}

void CheckPlayerWeaponFired::loadParams() {
    getDynamicParam(&mCheckFireType, "CheckFireType");
}

}  // namespace uking::query
