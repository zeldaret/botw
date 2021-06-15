#include "Game/AI/Query/queryCheckDieCnt.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckDieCnt::CheckDieCnt(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckDieCnt::~CheckDieCnt() = default;

int CheckDieCnt::doQuery() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm)
        return 0;

    sead::FixedSafeString<64> flag;
    flag.format("%s_DeathCount", mActorName.cstr());
    int count = 0;
    if (!gdm->getParamBypassPerm().get().getS32(&count, flag))
        return 0;

    return count > *mCount;
}

void CheckDieCnt::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Count");
    loadString(arg.param_accessor, "ActorName");
}

void CheckDieCnt::loadParams() {
    getDynamicParam(&mCount, "Count");
    getDynamicParam(&mActorName, "ActorName");
}

}  // namespace uking::query
