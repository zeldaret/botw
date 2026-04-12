#include "Game/AI/Query/queryCheckItemShopDecide.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckItemShopDecide::CheckItemShopDecide(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckItemShopDecide::~CheckItemShopDecide() = default;

int CheckItemShopDecide::doQuery() {
    bool isd = false;
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm != nullptr) {
        if (gdm->getParam().get().getBool(&isd, "Shop_IsDecide") && isd) {
            return 1;
        }
    }
    return 0;
}

void CheckItemShopDecide::loadParams(const evfl::QueryArg& arg) {}

void CheckItemShopDecide::loadParams() {}

}  // namespace uking::query
