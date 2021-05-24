#include "Game/AI/Query/queryCheckItemShopSelect.h"
#include <evfl/Query.h>

namespace uking::query {

CheckItemShopSelect::CheckItemShopSelect(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckItemShopSelect::~CheckItemShopSelect() = default;

// FIXME: implement
int CheckItemShopSelect::doQuery() {
    return -1;
}

void CheckItemShopSelect::loadParams(const evfl::QueryArg& arg) {}

void CheckItemShopSelect::loadParams() {}

}  // namespace uking::query
