#include "Game/AI/Query/queryHasItemDyeSpecifiedColor.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::query {

HasItemDyeSpecifiedColor::HasItemDyeSpecifiedColor(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

HasItemDyeSpecifiedColor::~HasItemDyeSpecifiedColor() = default;

int HasItemDyeSpecifiedColor::doQuery() {
    s32 sis = ksys::gdt::getFlag_Shop_ItemState();
    switch (sis) {
    case 0:
    case 9:
        return 1;
    case 8:
        return 0;
    default:
        break;
    }
    return 0;
}

void HasItemDyeSpecifiedColor::loadParams(const evfl::QueryArg& arg) {}

void HasItemDyeSpecifiedColor::loadParams() {}

}  // namespace uking::query
