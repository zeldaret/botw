#include "Game/AI/Query/queryCompareGameDataTime.h"
#include <evfl/query.h>

namespace uking::query {

CompareGameDataTime::CompareGameDataTime(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CompareGameDataTime::~CompareGameDataTime() = default;

// FIXME: implement
int CompareGameDataTime::doQuery() {
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
