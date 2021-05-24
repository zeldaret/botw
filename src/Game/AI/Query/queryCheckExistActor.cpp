#include "Game/AI/Query/queryCheckExistActor.h"
#include <evfl/Query.h>

namespace uking::query {

CheckExistActor::CheckExistActor(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckExistActor::~CheckExistActor() = default;

// FIXME: implement
int CheckExistActor::doQuery() {
    return -1;
}

void CheckExistActor::loadParams(const evfl::QueryArg& arg) {
    loadBool(arg.param_accessor, "IsCheckEquipStand");
    loadBool(arg.param_accessor, "IsCheckLife");
    loadString(arg.param_accessor, "ActorName");
}

void CheckExistActor::loadParams() {
    getDynamicParam(&mIsCheckEquipStand, "IsCheckEquipStand");
    getDynamicParam(&mIsCheckLife, "IsCheckLife");
    getDynamicParam(&mActorName, "ActorName");
}

}  // namespace uking::query
