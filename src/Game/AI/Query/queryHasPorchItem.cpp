#include "Game/AI/Query/queryHasPorchItem.h"
#include <evfl/Query.h>
#include "Game/UI/uiUtils.h"

namespace uking::query {

HasPorchItem::HasPorchItem(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasPorchItem::~HasPorchItem() = default;

int HasPorchItem::doQuery() {
    return ui::getItemValue(mPorchItemName) >= *mCount;
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
