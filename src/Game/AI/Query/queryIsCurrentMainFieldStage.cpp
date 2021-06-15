#include "Game/AI/Query/queryIsCurrentMainFieldStage.h"
#include <evfl/Query.h>

namespace uking::query {

IsCurrentMainFieldStage::IsCurrentMainFieldStage(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsCurrentMainFieldStage::~IsCurrentMainFieldStage() = default;

// FIXME: implement
int IsCurrentMainFieldStage::doQuery() {
    return -1;
}

void IsCurrentMainFieldStage::loadParams(const evfl::QueryArg& arg) {}

void IsCurrentMainFieldStage::loadParams() {}

}  // namespace uking::query
