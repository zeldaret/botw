#include "Game/AI/Query/queryIsCurrentAocFieldStage.h"
#include <evfl/Query.h>

namespace uking::query {

IsCurrentAocFieldStage::IsCurrentAocFieldStage(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsCurrentAocFieldStage::~IsCurrentAocFieldStage() = default;

// FIXME: implement
int IsCurrentAocFieldStage::doQuery() {
    return -1;
}

void IsCurrentAocFieldStage::loadParams(const evfl::QueryArg& arg) {}

void IsCurrentAocFieldStage::loadParams() {}

}  // namespace uking::query
