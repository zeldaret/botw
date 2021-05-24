#include "Game/AI/Query/queryIsNeedEquipWeapon.h"
#include <evfl/Query.h>

namespace uking::query {

IsNeedEquipWeapon::IsNeedEquipWeapon(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsNeedEquipWeapon::~IsNeedEquipWeapon() = default;

// FIXME: implement
int IsNeedEquipWeapon::doQuery() {
    return -1;
}

void IsNeedEquipWeapon::loadParams(const evfl::QueryArg& arg) {}

void IsNeedEquipWeapon::loadParams() {}

}  // namespace uking::query
