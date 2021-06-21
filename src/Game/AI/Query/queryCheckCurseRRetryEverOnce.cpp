#include "Game/AI/Query/queryCheckCurseRRetryEverOnce.h"
#include <evfl/Query.h>
#include "Game/DLC/aocChampionBalladManager.h"

namespace uking::query {

CheckCurseRRetryEverOnce::CheckCurseRRetryEverOnce(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckCurseRRetryEverOnce::~CheckCurseRRetryEverOnce() = default;

int CheckCurseRRetryEverOnce::doQuery() {
    auto* manager = ChampionBalladManager::instance();
    if (!manager)
        return 0;

    auto blight = BlightType(*mCurseRType);
    if (blight <= BlightType::Water)
        return manager->getBlightRematchCount(blight) > 0;
    return 0;
}

void CheckCurseRRetryEverOnce::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "CurseRType");
}

void CheckCurseRRetryEverOnce::loadParams() {
    getDynamicParam(&mCurseRType, "CurseRType");
}

}  // namespace uking::query
