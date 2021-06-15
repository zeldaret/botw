#include "Game/AI/Query/queryCheckDyeShopSelect.h"
#include <evfl/Query.h>

namespace uking::query {

CheckDyeShopSelect::CheckDyeShopSelect(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckDyeShopSelect::~CheckDyeShopSelect() = default;

// FIXME: implement
int CheckDyeShopSelect::doQuery() {
    return -1;
}

void CheckDyeShopSelect::loadParams(const evfl::QueryArg& arg) {}

void CheckDyeShopSelect::loadParams() {}

}  // namespace uking::query
