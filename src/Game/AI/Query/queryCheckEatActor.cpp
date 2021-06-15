#include "Game/AI/Query/queryCheckEatActor.h"
#include <evfl/Query.h>

namespace uking::query {

CheckEatActor::CheckEatActor(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckEatActor::~CheckEatActor() = default;

// FIXME: implement
int CheckEatActor::doQuery() {
    return -1;
}

void CheckEatActor::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "ActorName");
}

void CheckEatActor::loadParams() {
    getDynamicParam(&mActorName, "ActorName");
    getAITreeVariable(&mPrevEatActorName, "PrevEatActorName");
}

}  // namespace uking::query
