#include "Game/AI/Query/queryCheckPlacedItemSaled.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckPlacedItemSaled::CheckPlacedItemSaled(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPlacedItemSaled::~CheckPlacedItemSaled() = default;

int CheckPlacedItemSaled::doQuery() {
    auto* gdm = ksys::gdt::Manager::instance();
    int ics = 2;
    int ic = 2;
    if (gdm != nullptr) {
        gdm->getParamBypassPerm().get().getS32(&ics, "PlacedItemCountState");
        ic = ics;
        if (ic == 3) {
            ics = 1;
        }
    }
    return ics;
}

void CheckPlacedItemSaled::loadParams(const evfl::QueryArg& arg) {}

void CheckPlacedItemSaled::loadParams() {}

}  // namespace uking::query
