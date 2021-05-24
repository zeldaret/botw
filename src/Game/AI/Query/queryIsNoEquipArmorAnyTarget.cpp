#include "Game/AI/Query/queryIsNoEquipArmorAnyTarget.h"
#include <evfl/Query.h>

namespace uking::query {

IsNoEquipArmorAnyTarget::IsNoEquipArmorAnyTarget(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsNoEquipArmorAnyTarget::~IsNoEquipArmorAnyTarget() = default;

// FIXME: implement
int IsNoEquipArmorAnyTarget::doQuery() {
    return -1;
}

void IsNoEquipArmorAnyTarget::loadParams(const evfl::QueryArg& arg) {}

void IsNoEquipArmorAnyTarget::loadParams() {}

}  // namespace uking::query
