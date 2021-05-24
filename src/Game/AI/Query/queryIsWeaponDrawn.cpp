#include "Game/AI/Query/queryIsWeaponDrawn.h"
#include <evfl/Query.h>

namespace uking::query {

IsWeaponDrawn::IsWeaponDrawn(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsWeaponDrawn::~IsWeaponDrawn() = default;

// FIXME: implement
int IsWeaponDrawn::doQuery() {
    return -1;
}

void IsWeaponDrawn::loadParams(const evfl::QueryArg& arg) {}

void IsWeaponDrawn::loadParams() {}

}  // namespace uking::query
