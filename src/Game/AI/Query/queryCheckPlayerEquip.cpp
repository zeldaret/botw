#include "Game/AI/Query/queryCheckPlayerEquip.h"
#include <evfl/Query.h>

namespace uking::query {

CheckPlayerEquip::CheckPlayerEquip(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPlayerEquip::~CheckPlayerEquip() = default;

// FIXME: implement
int CheckPlayerEquip::doQuery() {
    return -1;
}

void CheckPlayerEquip::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "PlayerEquipType");
}

void CheckPlayerEquip::loadParams() {
    getDynamicParam(&mPlayerEquipType, "PlayerEquipType");
}

}  // namespace uking::query
