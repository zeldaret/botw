#include "Game/Actor/Query/queryBranchByDyeColor.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::query {

BranchByDyeColor::BranchByDyeColor(const InitArg& arg) : ksys::act::ai::Query(arg) {}

BranchByDyeColor::~BranchByDyeColor() = default;

int BranchByDyeColor::doQuery() {
    auto index = ksys::gdt::getFlag_ColorChange_MaterialIndex();
    if (index >= 1 && index <= 15) {
        return index;
    }
    return 0;
}

void BranchByDyeColor::loadParams(const evfl::QueryArg& arg) {}

void BranchByDyeColor::loadParams() {}

}  // namespace uking::query
