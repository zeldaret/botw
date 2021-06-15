#include "Game/AI/Query/queryCanCreateMakeItemList.h"
#include <evfl/Query.h>

namespace uking::query {

CanCreateMakeItemList::CanCreateMakeItemList(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CanCreateMakeItemList::~CanCreateMakeItemList() = default;

// FIXME: implement
int CanCreateMakeItemList::doQuery() {
    return -1;
}

void CanCreateMakeItemList::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "ShopType");
    loadBool(arg.param_accessor, "IncludePorchMainMat");
    loadBool(arg.param_accessor, "IncludePorchSubMat");
}

void CanCreateMakeItemList::loadParams() {
    getDynamicParam(&mShopType, "ShopType");
    getDynamicParam(&mIncludePorchMainMat, "IncludePorchMainMat");
    getDynamicParam(&mIncludePorchSubMat, "IncludePorchSubMat");
}

}  // namespace uking::query
