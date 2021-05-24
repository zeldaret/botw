#include "Game/AI/Query/queryCheckAppShopSelect.h"
#include <evfl/Query.h>

namespace uking::query {

CheckAppShopSelect::CheckAppShopSelect(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckAppShopSelect::~CheckAppShopSelect() = default;

// FIXME: implement
int CheckAppShopSelect::doQuery() {
    return -1;
}

void CheckAppShopSelect::loadParams(const evfl::QueryArg& arg) {}

void CheckAppShopSelect::loadParams() {}

}  // namespace uking::query
