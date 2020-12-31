#include "Game/AI/AI/aiLastBossRailWarpRoot.h"

namespace uking::ai {

LastBossRailWarpRoot::LastBossRailWarpRoot(const InitArg& arg) : LastBossNormalWarpRoot(arg) {}

LastBossRailWarpRoot::~LastBossRailWarpRoot() = default;

void LastBossRailWarpRoot::loadParams_() {
    LastBossNormalWarpRoot::loadParams_();
    getDynamicParam(&mRailIndex_d, "RailIndex");
}

}  // namespace uking::ai
