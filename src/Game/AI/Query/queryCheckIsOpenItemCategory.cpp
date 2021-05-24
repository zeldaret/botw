#include "Game/AI/Query/queryCheckIsOpenItemCategory.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::query {

CheckIsOpenItemCategory::CheckIsOpenItemCategory(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckIsOpenItemCategory::~CheckIsOpenItemCategory() = default;

int CheckIsOpenItemCategory::doQuery() {
    return !ksys::gdt::getFlag_IsOpenItemCategory(*mCategory);
}

void CheckIsOpenItemCategory::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Category");
}

void CheckIsOpenItemCategory::loadParams() {
    getDynamicParam(&mCategory, "Category");
}

}  // namespace uking::query
