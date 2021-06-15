#include "Game/AI/Query/queryBranchByGameOver.h"
#include <evfl/Query.h>

namespace uking::query {

BranchByGameOver::BranchByGameOver(const InitArg& arg) : ksys::act::ai::Query(arg) {}

BranchByGameOver::~BranchByGameOver() = default;

// FIXME: implement
int BranchByGameOver::doQuery() {
    return -1;
}

void BranchByGameOver::loadParams(const evfl::QueryArg& arg) {}

void BranchByGameOver::loadParams() {}

}  // namespace uking::query
