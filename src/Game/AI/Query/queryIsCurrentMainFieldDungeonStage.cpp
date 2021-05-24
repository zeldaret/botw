#include "Game/AI/Query/queryIsCurrentMainFieldDungeonStage.h"
#include <evfl/Query.h>

namespace uking::query {

IsCurrentMainFieldDungeonStage::IsCurrentMainFieldDungeonStage(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

IsCurrentMainFieldDungeonStage::~IsCurrentMainFieldDungeonStage() = default;

// FIXME: implement
int IsCurrentMainFieldDungeonStage::doQuery() {
    return -1;
}

void IsCurrentMainFieldDungeonStage::loadParams(const evfl::QueryArg& arg) {}

void IsCurrentMainFieldDungeonStage::loadParams() {}

}  // namespace uking::query
