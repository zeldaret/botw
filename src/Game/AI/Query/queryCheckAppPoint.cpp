#include "Game/AI/Query/queryCheckAppPoint.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::query {

CheckAppPoint::CheckAppPoint(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckAppPoint::~CheckAppPoint() = default;

int CheckAppPoint::doQuery() {
    s32 reach = ksys::gdt::getS32ByKey("ReachPointActorDiscoverNum");
    s32 use = ksys::gdt::getS32ByKey("App_ExtendUsePoint");
    return reach - use > 1;
}

void CheckAppPoint::loadParams(const evfl::QueryArg& arg) {}

void CheckAppPoint::loadParams() {}

}  // namespace uking::query
