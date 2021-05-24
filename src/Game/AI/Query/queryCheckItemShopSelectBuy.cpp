#include "Game/AI/Query/queryCheckItemShopSelectBuy.h"
#include <evfl/Query.h>

namespace uking::query {

CheckItemShopSelectBuy::CheckItemShopSelectBuy(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckItemShopSelectBuy::~CheckItemShopSelectBuy() = default;

// FIXME: implement
int CheckItemShopSelectBuy::doQuery() {
    return -1;
}

void CheckItemShopSelectBuy::loadParams(const evfl::QueryArg& arg) {}

void CheckItemShopSelectBuy::loadParams() {}

}  // namespace uking::query
