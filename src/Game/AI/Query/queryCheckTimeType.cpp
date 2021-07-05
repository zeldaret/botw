#include "Game/AI/Query/queryCheckTimeType.h"
#include <evfl/Query.h>
#include "KingSystem/World/worldManager.h"

namespace uking::query {

CheckTimeType::CheckTimeType(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckTimeType::~CheckTimeType() = default;

int CheckTimeType::doQuery() {
    auto* wm = ksys::world::Manager::instance();
    if (wm == nullptr)
        return 0;

    auto* tm = wm->getTimeMgr();
    if (tm == nullptr)
        return 0;

    u32 division = tm->getTimeDivision();
    if (division < 8)
        return division;
    return 0;
}

void CheckTimeType::loadParams(const evfl::QueryArg& arg) {}

void CheckTimeType::loadParams() {}

}  // namespace uking::query
