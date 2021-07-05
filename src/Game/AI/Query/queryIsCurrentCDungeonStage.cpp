#include "Game/AI/Query/queryIsCurrentCDungeonStage.h"
#include <evfl/Query.h>
#include "KingSystem/System/StageInfo.h"

namespace uking::query {

IsCurrentCDungeonStage::IsCurrentCDungeonStage(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsCurrentCDungeonStage::~IsCurrentCDungeonStage() = default;

int IsCurrentCDungeonStage::doQuery() {
    return ksys::StageInfo::sIsCDungeon;
}

void IsCurrentCDungeonStage::loadParams(const evfl::QueryArg& arg) {}

void IsCurrentCDungeonStage::loadParams() {}

}  // namespace uking::query
