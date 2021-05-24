#include "Game/AI/Query/queryHasSetItem.h"
#include <evfl/Query.h>

namespace uking::query {

HasSetItem::HasSetItem(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasSetItem::~HasSetItem() = default;

// FIXME: implement
int HasSetItem::doQuery() {
    return -1;
}

void HasSetItem::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Count");
    loadString(arg.param_accessor, "ItemName");
}

void HasSetItem::loadParams() {
    getDynamicParam(&mCount, "Count");
    getDynamicParam(&mItemName, "ItemName");
}

}  // namespace uking::query
