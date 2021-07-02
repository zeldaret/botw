#include "Game/AI/Query/queryIsOnInstEventFlag.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::query {

IsOnInstEventFlag::IsOnInstEventFlag(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsOnInstEventFlag::~IsOnInstEventFlag() = default;

int IsOnInstEventFlag::doQuery() {
    return mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::InstEvent);
}

void IsOnInstEventFlag::loadParams(const evfl::QueryArg& arg) {}

void IsOnInstEventFlag::loadParams() {}

}  // namespace uking::query
