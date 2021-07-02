#include "Game/AI/Query/queryCheckSellResult.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::query {

CheckSellResult::CheckSellResult(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckSellResult::~CheckSellResult() = default;

int CheckSellResult::doQuery() {
    if (ksys::gdt::getFlag_Shop_IsDecide()) {
        s32 flag = ksys::gdt::getFlag_Shop_CurrentItemState();
        if (flag == 0)
            return 0;
        if (flag == 0xD)
            return 1;
        if (flag == 0xE)
            return 2;
    }
    return 3;
}

void CheckSellResult::loadParams(const evfl::QueryArg& arg) {}

void CheckSellResult::loadParams() {}

}  // namespace uking::query
