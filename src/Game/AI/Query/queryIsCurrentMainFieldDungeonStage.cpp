#include "Game/AI/Query/queryIsCurrentMainFieldDungeonStage.h"
#include <evfl/Query.h>
#include "KingSystem/System/StageInfo.h"

namespace uking::query {

IsCurrentMainFieldDungeonStage::IsCurrentMainFieldDungeonStage(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

IsCurrentMainFieldDungeonStage::~IsCurrentMainFieldDungeonStage() = default;

int IsCurrentMainFieldDungeonStage::doQuery() {
    return ksys::StageInfo::sIsMainFieldDungeon;
}

void IsCurrentMainFieldDungeonStage::loadParams(const evfl::QueryArg& arg) {}

void IsCurrentMainFieldDungeonStage::loadParams() {}

}  // namespace uking::query
