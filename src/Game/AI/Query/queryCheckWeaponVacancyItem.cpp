#include "Game/AI/Query/queryCheckWeaponVacancyItem.h"
#include <evfl/Query.h>

namespace uking::query {

CheckWeaponVacancyItem::CheckWeaponVacancyItem(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckWeaponVacancyItem::~CheckWeaponVacancyItem() = default;

// FIXME: implement
int CheckWeaponVacancyItem::doQuery() {
    return -1;
}

void CheckWeaponVacancyItem::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Count");
}

void CheckWeaponVacancyItem::loadParams() {
    getDynamicParam(&mCount, "Count");
}

}  // namespace uking::query
