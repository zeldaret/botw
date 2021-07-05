#include "Game/AI/Query/queryHasPouchItemByPouchCategory.h"
#include <evfl/Query.h>
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/actTag.h"

namespace uking::query {

HasPouchItemByPouchCategory::HasPouchItemByPouchCategory(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

HasPouchItemByPouchCategory::~HasPouchItemByPouchCategory() = default;

int HasPouchItemByPouchCategory::doQuery() {
    s32 result = 0;
    using namespace ksys::act::tags;

    auto* pm = ui::PauseMenuDataMgr::instance();
    if (pm == nullptr)
        return 1;

    switch (*mCategory) {
    case 0:
        result = pm->countItemsWithCategory(ui::PouchCategory::Sword);
        break;
    case 1:
        result = pm->countItemsWithProfile("WeaponBow", false);
        break;
    case 2:
        result = pm->countItemsWithTag(Arrow, false);
        break;
    case 3:
        result = pm->countItemsWithCategory(ui::PouchCategory::Shield);
        break;
    case 4:
        result = pm->countItemsWithCategory(ui::PouchCategory::Armor);
        break;
    case 5:
        result = pm->countItemsWithCategory(ui::PouchCategory::Material);
        break;
    case 6:
        result = pm->countItemsWithCategory(ui::PouchCategory::Food);
        break;
    case 7:
        result = pm->countItemsWithCategory(ui::PouchCategory::KeyItem);
        break;
    default:
        result = 0;
        break;
    }
    return result < *mCount;
}

void HasPouchItemByPouchCategory::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Category");
    loadInt(arg.param_accessor, "Count");
}

void HasPouchItemByPouchCategory::loadParams() {
    getDynamicParam(&mCategory, "Category");
    getDynamicParam(&mCount, "Count");
}

}  // namespace uking::query
