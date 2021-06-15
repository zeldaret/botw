#include "Game/AI/Query/queryCheckEquipment.h"
#include <evfl/Query.h>

namespace uking::query {

CheckEquipment::CheckEquipment(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckEquipment::~CheckEquipment() = default;

// FIXME: implement
int CheckEquipment::doQuery() {
    return -1;
}

void CheckEquipment::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "EquipItemName");
}

void CheckEquipment::loadParams() {
    getDynamicParam(&mEquipItemName, "EquipItemName");
}

}  // namespace uking::query
