#include "Game/AI/Query/queryCheckAppShopSelect.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckAppShopSelect::CheckAppShopSelect(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckAppShopSelect::~CheckAppShopSelect() = default;

int CheckAppShopSelect::doQuery() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm != nullptr) {
        int screen_type = -1;
        if (gdm->getParam().get().getS32(&screen_type, "Shop_ScreenType")) {
            if (screen_type == 15) {
                return 0;
            }
            if (screen_type == 0) {
                return 1;
            }
        }
    }
    return 1;
}

void CheckAppShopSelect::loadParams(const evfl::QueryArg& arg) {}

void CheckAppShopSelect::loadParams() {}

}  // namespace uking::query
