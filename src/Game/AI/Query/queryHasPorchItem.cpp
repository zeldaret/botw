#include "Game/AI/Query/queryHasPorchItem.h"
#include <evfl/Query.h>

namespace uking::query {

HasPorchItem::HasPorchItem(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasPorchItem::~HasPorchItem() = default;

// FIXME: implement
int HasPorchItem::doQuery() {
    return -1;
}

void HasPorchItem::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Count");
    loadString(arg.param_accessor, "PorchItemName");
}

void HasPorchItem::loadParams() {
    getDynamicParam(&mCount, "Count");
    getDynamicParam(&mPorchItemName, "PorchItemName");
}

}  // namespace uking::query
