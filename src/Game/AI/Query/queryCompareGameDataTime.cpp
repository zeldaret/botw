#include "Game/AI/Query/queryCompareGameDataTime.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CompareGameDataTime::CompareGameDataTime(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CompareGameDataTime::~CompareGameDataTime() = default;

int CompareGameDataTime::doQuery() {
    int min_a{};
    int sec_a{};
    int milli_a{};
    int min_b{};
    int sec_b{};
    int milli_b{};

    auto* gdt = ksys::gdt::Manager::instance();
    if (!gdt)
        return 0;
    if (!gdt->getParamBypassPerm().get().getS32(&min_a, mGameDataIntMinA))
        return 0;
    if (!gdt->getParamBypassPerm().get().getS32(&sec_a, mGameDataIntSecA))
        return 0;
    if (!gdt->getParamBypassPerm().get().getS32(&milli_a, mGameDataIntMilliA))
        return 0;
    if (!gdt->getParamBypassPerm().get().getS32(&min_b, mGameDataIntMinB))
        return 0;
    if (!gdt->getParamBypassPerm().get().getS32(&sec_b, mGameDataIntSecB))
        return 0;
    if (!gdt->getParamBypassPerm().get().getS32(&milli_b, mGameDataIntMilliB))
        return 0;

    const int time_a = (60 * 1000 * min_a) + (1000 * sec_a) + milli_a;
    const int time_b = (60 * 1000 * min_b) + (1000 * sec_b) + milli_b;

    if (time_a < time_b)
        return 0;
    if (time_a == time_b)
        return 1;
    if (time_a != time_b)
        return 2;
    SEAD_ASSERT(false);
    return -1;
}

void CompareGameDataTime::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "GameDataIntMinA");
    loadString(arg.param_accessor, "GameDataIntSecA");
    loadString(arg.param_accessor, "GameDataIntMilliA");
    loadString(arg.param_accessor, "GameDataIntMinB");
    loadString(arg.param_accessor, "GameDataIntSecB");
    loadString(arg.param_accessor, "GameDataIntMilliB");
}

void CompareGameDataTime::loadParams() {
    getDynamicParam(&mGameDataIntMinA, "GameDataIntMinA");
    getDynamicParam(&mGameDataIntSecA, "GameDataIntSecA");
    getDynamicParam(&mGameDataIntMilliA, "GameDataIntMilliA");
    getDynamicParam(&mGameDataIntMinB, "GameDataIntMinB");
    getDynamicParam(&mGameDataIntSecB, "GameDataIntSecB");
    getDynamicParam(&mGameDataIntMilliB, "GameDataIntMilliB");
}

}  // namespace uking::query
