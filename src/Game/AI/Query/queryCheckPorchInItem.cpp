#include "Game/AI/Query/queryCheckPorchInItem.h"
#include <evfl/Query.h>

namespace uking::query {

CheckPorchInItem::CheckPorchInItem(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPorchInItem::~CheckPorchInItem() = default;

// FIXME: implement
int CheckPorchInItem::doQuery() {
    return -1;
}

void CheckPorchInItem::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "PorchItemName");
}

void CheckPorchInItem::loadParams() {
    getDynamicParam(&mPorchItemName, "PorchItemName");
}

}  // namespace uking::query
