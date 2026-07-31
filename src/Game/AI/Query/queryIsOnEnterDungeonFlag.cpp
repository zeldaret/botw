#include "Game/AI/Query/queryIsOnEnterDungeonFlag.h"
#include <evfl/Query.h>
#include "Game/gameScene.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::query {

IsOnEnterDungeonFlag::IsOnEnterDungeonFlag(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsOnEnterDungeonFlag::~IsOnEnterDungeonFlag() = default;

int IsOnEnterDungeonFlag::doQuery() {
    return ksys::gdt::isDungeonEntered(GameScene::getCurrentMapName(), false);
}

void IsOnEnterDungeonFlag::loadParams(const evfl::QueryArg& arg) {}

void IsOnEnterDungeonFlag::loadParams() {}

}  // namespace uking::query
