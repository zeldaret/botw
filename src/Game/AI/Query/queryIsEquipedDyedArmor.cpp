#include "Game/AI/Query/queryIsEquipedDyedArmor.h"
#include <evfl/Query.h>

namespace uking::query {

IsEquipedDyedArmor::IsEquipedDyedArmor(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsEquipedDyedArmor::~IsEquipedDyedArmor() = default;

// FIXME: implement
int IsEquipedDyedArmor::doQuery() {
    return -1;
}

void IsEquipedDyedArmor::loadParams(const evfl::QueryArg& arg) {}

void IsEquipedDyedArmor::loadParams() {}

}  // namespace uking::query
