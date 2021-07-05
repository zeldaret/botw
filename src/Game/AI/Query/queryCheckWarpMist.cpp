#include "Game/AI/Query/queryCheckWarpMist.h"
#include <evfl/Query.h>
#include "KingSystem/World/worldManager.h"

namespace uking::query {

CheckWarpMist::CheckWarpMist(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckWarpMist::~CheckWarpMist() = default;

int CheckWarpMist::doQuery() {
    return ksys::world::Manager::instance()->getEnvMgr()->getWarpMistIntensity() > 0.0f;
}

void CheckWarpMist::loadParams(const evfl::QueryArg& arg) {}

void CheckWarpMist::loadParams() {}

}  // namespace uking::query
