#include "Game/AI/Query/queryHasSetItem.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

HasSetItem::HasSetItem(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasSetItem::~HasSetItem() = default;

// NON_MATCHING: temp duplication
int HasSetItem::doQuery() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm == nullptr)
        return 0;

    auto flag_type = gdm->getParam().get1().getBuffer()->getFlagType(mItemName);

    if (flag_type == ksys::gdt::FlagType::Bool) {
        bool value = false;
        if (gdm->getParamBypassPerm().get().getBool(&value, mItemName))
            return value;
    } else if (flag_type == ksys::gdt::FlagType::S32) {
        s32 value = 0;
        if (gdm->getParamBypassPerm().get().getS32(&value, mItemName))
            return value >= *mCount;
    }
    return 0;
}

void HasSetItem::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Count");
    loadString(arg.param_accessor, "ItemName");
}

void HasSetItem::loadParams() {
    getDynamicParam(&mCount, "Count");
    getDynamicParam(&mItemName, "ItemName");
}

}  // namespace uking::query
