#include "Game/AI/Query/queryCheckEquipArmorSeriesType.h"
#include <evfl/Query.h>

namespace uking::query {

CheckEquipArmorSeriesType::CheckEquipArmorSeriesType(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckEquipArmorSeriesType::~CheckEquipArmorSeriesType() = default;

// FIXME: implement
int CheckEquipArmorSeriesType::doQuery() {
    return -1;
}

void CheckEquipArmorSeriesType::loadParams(const evfl::QueryArg& arg) {
    loadBool(arg.param_accessor, "CheckHead");
    loadBool(arg.param_accessor, "CheckUpper");
    loadBool(arg.param_accessor, "CheckLower");
    loadString(arg.param_accessor, "CheckType");
}

void CheckEquipArmorSeriesType::loadParams() {
    getDynamicParam(&mCheckHead, "CheckHead");
    getDynamicParam(&mCheckUpper, "CheckUpper");
    getDynamicParam(&mCheckLower, "CheckLower");
    getDynamicParam(&mCheckType, "CheckType");
}

}  // namespace uking::query
