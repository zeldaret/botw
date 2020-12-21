#include "Game/AI/Query/queryCheckIsOpenItemCategory.h"
#include <evfl/query.h>

namespace uking::query {

CheckIsOpenItemCategory::CheckIsOpenItemCategory(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckIsOpenItemCategory::~CheckIsOpenItemCategory() = default;

// FIXME: implement
int CheckIsOpenItemCategory::doQuery() {
    return -1;
}

void CheckIsOpenItemCategory::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Category");
}

void CheckIsOpenItemCategory::loadParams() {
    getDynamicParam(&mCategory, "Category");
}

}  // namespace uking::query
