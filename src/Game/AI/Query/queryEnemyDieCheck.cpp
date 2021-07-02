#include "Game/AI/Query/queryEnemyDieCheck.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::query {

EnemyDieCheck::EnemyDieCheck(const InitArg& arg) : ksys::act::ai::Query(arg) {}

EnemyDieCheck::~EnemyDieCheck() = default;

int EnemyDieCheck::doQuery() {
    return mActor->getActorFlags2().isOff(ksys::act::Actor::ActorFlag2::Alive);
}

void EnemyDieCheck::loadParams(const evfl::QueryArg& arg) {}

void EnemyDieCheck::loadParams() {}

}  // namespace uking::query
