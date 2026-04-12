#include "Game/AI/Query/queryCheckAppShopSelect.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckAppShopSelect::CheckAppShopSelect(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckAppShopSelect::~CheckAppShopSelect() = default;

int CheckAppShopSelect::doQuery() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm != nullptr) {
        int as = -1;
        if (gdm->getParam().get().getS32(&as, "Shop_ScreenType")) {
            if (as == 15) {
                return 0;
            }
            if (as == 0) {
                return 1;
            }
        }
    }
    return 1;
}

void CheckAppShopSelect::loadParams(const evfl::QueryArg& arg) {}

void CheckAppShopSelect::loadParams() {}

}  // namespace uking::query
