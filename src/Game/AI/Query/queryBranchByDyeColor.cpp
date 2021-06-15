#include "Game/AI/Query/queryBranchByDyeColor.h"
#include <evfl/Query.h>

namespace uking::query {

BranchByDyeColor::BranchByDyeColor(const InitArg& arg) : ksys::act::ai::Query(arg) {}

BranchByDyeColor::~BranchByDyeColor() = default;

// FIXME: implement
int BranchByDyeColor::doQuery() {
    return -1;
}

void BranchByDyeColor::loadParams(const evfl::QueryArg& arg) {}

void BranchByDyeColor::loadParams() {}

}  // namespace uking::query
