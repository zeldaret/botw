#include "Game/AI/Query/queryIsOnEnterDungeonFlag.h"
#include <evfl/Query.h>

namespace uking::query {

IsOnEnterDungeonFlag::IsOnEnterDungeonFlag(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsOnEnterDungeonFlag::~IsOnEnterDungeonFlag() = default;

// FIXME: implement
int IsOnEnterDungeonFlag::doQuery() {
    return -1;
}

void IsOnEnterDungeonFlag::loadParams(const evfl::QueryArg& arg) {}

void IsOnEnterDungeonFlag::loadParams() {}

}  // namespace uking::query
