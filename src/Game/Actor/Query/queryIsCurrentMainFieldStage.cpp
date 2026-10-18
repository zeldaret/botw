#include "Game/Actor/Query/queryIsCurrentMainFieldStage.h"
#include <evfl/Query.h>
#include "Game/Scene/gameStageInfo.h"

namespace uking::query {

IsCurrentMainFieldStage::IsCurrentMainFieldStage(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsCurrentMainFieldStage::~IsCurrentMainFieldStage() = default;

int IsCurrentMainFieldStage::doQuery() {
    return StageInfo::getCurrentMapType() == "MainField";
}

void IsCurrentMainFieldStage::loadParams(const evfl::QueryArg& arg) {}

void IsCurrentMainFieldStage::loadParams() {}

}  // namespace uking::query
