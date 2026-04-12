#include "Game/AI/Query/queryCheckItemShopPorchVacancy.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckItemShopPorchVacancy::CheckItemShopPorchVacancy(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckItemShopPorchVacancy::~CheckItemShopPorchVacancy() = default;

int CheckItemShopPorchVacancy::doQuery() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm != nullptr) {
        int isp = -1;
        if (gdm->getParam().get().getS32(&isp, "Shop_CurrentItemState") && (isp == 7)) {
            return 0;
        }
    }
    return 1;
}

void CheckItemShopPorchVacancy::loadParams(const evfl::QueryArg& arg) {}

void CheckItemShopPorchVacancy::loadParams() {}

}  // namespace uking::query
