#include "Game/Actor/Query/queryIsCurrentMainFieldStage.h"
#include <evfl/Query.h>
#include "Game/gameScene.h"

namespace uking::query {

IsCurrentMainFieldStage::IsCurrentMainFieldStage(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsCurrentMainFieldStage::~IsCurrentMainFieldStage() = default;

int IsCurrentMainFieldStage::doQuery() {
    return GameScene::getCurrentMapType() == "MainField";
}

void IsCurrentMainFieldStage::loadParams(const evfl::QueryArg& arg) {}

void IsCurrentMainFieldStage::loadParams() {}

}  // namespace uking::query
