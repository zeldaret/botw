#include "Game/AI/Query/queryIsItemInStock.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

IsItemInStock::IsItemInStock(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsItemInStock::~IsItemInStock() = default;

int IsItemInStock::doQuery() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm != nullptr) {
        s32 state = -1;
        if (!gdm->getParam().get().getS32(&state, "Shop_CurrentItemState"))
            return 1;
        if (state == 1)
            return 0;
    }
    return 1;
}

void IsItemInStock::loadParams(const evfl::QueryArg& arg) {}

void IsItemInStock::loadParams() {}

}  // namespace uking::query
