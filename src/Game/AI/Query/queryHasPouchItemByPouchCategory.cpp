#include "Game/AI/Query/queryHasPouchItemByPouchCategory.h"
#include <evfl/Query.h>

namespace uking::query {

HasPouchItemByPouchCategory::HasPouchItemByPouchCategory(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

HasPouchItemByPouchCategory::~HasPouchItemByPouchCategory() = default;

// FIXME: implement
int HasPouchItemByPouchCategory::doQuery() {
    return -1;
}

void HasPouchItemByPouchCategory::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Category");
    loadInt(arg.param_accessor, "Count");
}

void HasPouchItemByPouchCategory::loadParams() {
    getDynamicParam(&mCategory, "Category");
    getDynamicParam(&mCount, "Count");
}

}  // namespace uking::query
