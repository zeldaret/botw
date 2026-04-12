#include "Game/AI/Query/queryCheckDyeShopSelect.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckDyeShopSelect::CheckDyeShopSelect(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckDyeShopSelect::~CheckDyeShopSelect() = default;

int CheckDyeShopSelect::doQuery() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm != nullptr) {
        int ds = -1;
        if (gdm->getParam().get().getS32(&ds, "Shop_ScreenType") && (ds != 0)) {
            if (ds == 9) {
                return 0;
            }
            if (ds == 10) {
                return 1;
            }
        }
    }
    return 2;
}

void CheckDyeShopSelect::loadParams(const evfl::QueryArg& arg) {}

void CheckDyeShopSelect::loadParams() {}

}  // namespace uking::query
