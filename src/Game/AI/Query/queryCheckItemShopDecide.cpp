#include "Game/AI/Query/queryCheckItemShopDecide.h"
#include <evfl/Query.h>

namespace uking::query {

CheckItemShopDecide::CheckItemShopDecide(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckItemShopDecide::~CheckItemShopDecide() = default;

// FIXME: implement
int CheckItemShopDecide::doQuery() {
    return -1;
}

void CheckItemShopDecide::loadParams(const evfl::QueryArg& arg) {}

void CheckItemShopDecide::loadParams() {}

}  // namespace uking::query
