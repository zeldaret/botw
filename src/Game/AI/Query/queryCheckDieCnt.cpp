#include "Game/AI/Query/queryCheckDieCnt.h"
#include <evfl/query.h>

namespace uking::query {

CheckDieCnt::CheckDieCnt(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckDieCnt::~CheckDieCnt() = default;

// FIXME: implement
int CheckDieCnt::doQuery() {
    return -1;
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
