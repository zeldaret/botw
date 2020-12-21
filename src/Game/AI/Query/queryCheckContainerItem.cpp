#include "Game/AI/Query/queryCheckContainerItem.h"
#include <evfl/query.h>

namespace uking::query {

CheckContainerItem::CheckContainerItem(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckContainerItem::~CheckContainerItem() = default;

// FIXME: implement
int CheckContainerItem::doQuery() {
    return -1;
}

void CheckContainerItem::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "PorchItemName");
}

void CheckContainerItem::loadParams() {
    getDynamicParam(&mPorchItemName, "PorchItemName");
}

}  // namespace uking::query
