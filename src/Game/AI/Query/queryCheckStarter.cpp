#include "Game/AI/Query/queryCheckStarter.h"
#include <evfl/Query.h>

namespace uking::query {

CheckStarter::CheckStarter(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckStarter::~CheckStarter() = default;

// FIXME: implement
int CheckStarter::doQuery() {
    return -1;
}

void CheckStarter::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "ActorName");
    loadString(arg.param_accessor, "UniqueName");
}

void CheckStarter::loadParams() {
    getDynamicParam(&mActorName, "ActorName");
    getDynamicParam(&mUniqueName, "UniqueName");
}

}  // namespace uking::query
