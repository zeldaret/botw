#include "Game/AI/Query/queryBranchByDyeColor.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::query {

BranchByDyeColor::BranchByDyeColor(const InitArg& arg) : ksys::act::ai::Query(arg) {}

BranchByDyeColor::~BranchByDyeColor() = default;

int BranchByDyeColor::doQuery() {
    auto ccm = ksys::gdt::getFlag_ColorChange_MaterialIndex();
    if (ccm >= 1 && ccm <= 15) {
        return ccm;
    }
    return 0;
}

void BranchByDyeColor::loadParams(const evfl::QueryArg& arg) {}

void BranchByDyeColor::loadParams() {}

}  // namespace uking::query
