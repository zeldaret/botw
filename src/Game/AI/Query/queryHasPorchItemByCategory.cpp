#include "Game/AI/Query/queryHasPorchItemByCategory.h"
#include <evfl/Query.h>

namespace uking::query {

HasPorchItemByCategory::HasPorchItemByCategory(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasPorchItemByCategory::~HasPorchItemByCategory() = default;

// FIXME: implement
int HasPorchItemByCategory::doQuery() {
    return -1;
}

void HasPorchItemByCategory::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Category");
    loadInt(arg.param_accessor, "Count");
}

void HasPorchItemByCategory::loadParams() {
    getDynamicParam(&mCategory, "Category");
    getDynamicParam(&mCount, "Count");
}

}  // namespace uking::query
