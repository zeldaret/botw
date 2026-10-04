#include "Game/Actor/Query/queryCheckItemShopSelectBuy.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckItemShopSelectBuy::CheckItemShopSelectBuy(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckItemShopSelectBuy::~CheckItemShopSelectBuy() = default;

int CheckItemShopSelectBuy::doQuery() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm != nullptr) {
        int screen_type = -1;
        if (gdm->getParam().get().getS32(&screen_type, "Shop_ScreenType")) {
            return screen_type != 1;
        }
    }
    return 0;
}

void CheckItemShopSelectBuy::loadParams(const evfl::QueryArg& arg) {}

void CheckItemShopSelectBuy::loadParams() {}

}  // namespace uking::query
