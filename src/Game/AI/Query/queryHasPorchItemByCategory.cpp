#include "Game/AI/Query/queryHasPorchItemByCategory.h"
#include <evfl/Query.h>
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/actTag.h"

namespace uking::query {

HasPorchItemByCategory::HasPorchItemByCategory(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasPorchItemByCategory::~HasPorchItemByCategory() = default;

int HasPorchItemByCategory::doQuery() {
    s32 result = 0;
    using namespace ksys::act::tags;

    auto* pm = ui::PauseMenuDataMgr::instance();
    if (pm == nullptr)
        return 1;

    switch (*mCategory) {
    case 0:
        result = pm->countItemsWithProfile("WeaponBow", true);
        break;
    case 1:
        result = pm->countItemsWithProfile("WeaponShield", true);
        break;
    case 2:
        result = pm->countItemsWithProfile("WeaponSpear", true);
        break;
    case 3:
        result = pm->countItemsWithProfile("WeaponSmallSword", true);
        break;
    case 4:
        result = pm->countItemsWithTag(Arrow, false);
        break;
    case 16:
        result = pm->countItemsWithTag(Arrow, true);
        break;
    case 5:
        result = pm->countItemsWithProfile("WeaponLargeSword", true);
        break;
    case 6:
        result = pm->countItemsWithTag(CookMushroom, true);
        break;
    case 7:
        result = pm->countItemsWithTag(RoastItem, true);
        break;
    case 8:
        result = pm->countItemsWithTag(CookFruit, true);
        break;
    case 9:
        result = pm->countItemsWithTag(CookOre, true);
        break;
    case 10:
        result = pm->countItemsWithTag(CookPlant, true);
        break;
    case 11:
        result = pm->countItemsWithTag(EnemyMaterial, true);
        break;
    case 12:
        result = pm->countItemsWithTag(CookMeat, true);
        break;
    case 13:
        result = pm->countItemsWithTag(CookMaterial, true);
        break;
    case 14:
        result = pm->countItemsWithProfile("HorseReins", true);
        break;
    case 15:
        result = pm->countItemsWithProfile("HorseSaddle", true);
        break;
    default:
        result = 0;
        break;
    }

    return result < *mCount;
}

void HasPorchItemByCategory::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Category");
    loadInt(arg.param_accessor, "Count");
}

void HasPorchItemByCategory::loadParams() {
    getDynamicParam(&mCategory, "Category");
    getDynamicParam(&mCount, "Count");
}

}  // namespace uking::query
