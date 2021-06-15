#include "Game/AI/Query/queryCheckStage.h"
#include <evfl/Query.h>

namespace uking::query {

CheckStage::CheckStage(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckStage::~CheckStage() = default;

// FIXME: implement
int CheckStage::doQuery() {
    return -1;
}

void CheckStage::loadParams(const evfl::QueryArg& arg) {}

void CheckStage::loadParams() {}

}  // namespace uking::query
