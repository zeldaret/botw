#include "Game/AI/Query/queryCheckShopSelectedItemName.h"
#include <evfl/Query.h>

namespace uking::query {

CheckShopSelectedItemName::CheckShopSelectedItemName(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckShopSelectedItemName::~CheckShopSelectedItemName() = default;

// FIXME: implement
int CheckShopSelectedItemName::doQuery() {
    return -1;
}

void CheckShopSelectedItemName::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "PorchItemName");
}

void CheckShopSelectedItemName::loadParams() {
    getDynamicParam(&mPorchItemName, "PorchItemName");
}

}  // namespace uking::query
