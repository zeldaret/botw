#include "Game/AI/Query/queryCheckPlacedItemSaled.h"
#include <evfl/Query.h>

namespace uking::query {

CheckPlacedItemSaled::CheckPlacedItemSaled(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPlacedItemSaled::~CheckPlacedItemSaled() = default;

// FIXME: implement
int CheckPlacedItemSaled::doQuery() {
    return -1;
}

void CheckPlacedItemSaled::loadParams(const evfl::QueryArg& arg) {}

void CheckPlacedItemSaled::loadParams() {}

}  // namespace uking::query
