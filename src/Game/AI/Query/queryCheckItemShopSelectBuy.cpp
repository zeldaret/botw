#include "Game/AI/Query/queryCheckItemShopSelectBuy.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckItemShopSelectBuy::CheckItemShopSelectBuy(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckItemShopSelectBuy::~CheckItemShopSelectBuy() = default;

int CheckItemShopSelectBuy::doQuery() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm != nullptr) {
        int is = -1;
        if (gdm->getParam().get().getS32(&is, "Shop_ScreenType")) {
            return is != 1;
        }
    }
    return 0;
}

void CheckItemShopSelectBuy::loadParams(const evfl::QueryArg& arg) {}

void CheckItemShopSelectBuy::loadParams() {}

}  // namespace uking::query
