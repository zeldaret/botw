#include "Game/AI/Query/queryCheckEquipItemType.h"
#include <evfl/query.h>

namespace uking::query {

CheckEquipItemType::CheckEquipItemType(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckEquipItemType::~CheckEquipItemType() = default;

// FIXME: implement
int CheckEquipItemType::doQuery() {
    return -1;
}

void CheckEquipItemType::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "CheckTargetActorName");
}

void CheckEquipItemType::loadParams() {
    getDynamicParam(&mCheckTargetActorName, "CheckTargetActorName");
}

}  // namespace uking::query
