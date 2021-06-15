#include "Game/AI/Query/queryCheckAddPorchItem.h"
#include <evfl/Query.h>

namespace uking::query {

CheckAddPorchItem::CheckAddPorchItem(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckAddPorchItem::~CheckAddPorchItem() = default;

// FIXME: implement
int CheckAddPorchItem::doQuery() {
    return -1;
}

void CheckAddPorchItem::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Count");
    loadString(arg.param_accessor, "PorchItemName");
}

void CheckAddPorchItem::loadParams() {
    getDynamicParam(&mCount, "Count");
    getDynamicParam(&mPorchItemName, "PorchItemName");
}

}  // namespace uking::query
