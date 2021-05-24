#include "Game/AI/Query/queryIsCurrentCDungeonStage.h"
#include <evfl/Query.h>

namespace uking::query {

IsCurrentCDungeonStage::IsCurrentCDungeonStage(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsCurrentCDungeonStage::~IsCurrentCDungeonStage() = default;

// FIXME: implement
int IsCurrentCDungeonStage::doQuery() {
    return -1;
}

void IsCurrentCDungeonStage::loadParams(const evfl::QueryArg& arg) {}

void IsCurrentCDungeonStage::loadParams() {}

}  // namespace uking::query
