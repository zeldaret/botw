#include "Game/AI/Query/queryCheckActorAction.h"
#include <evfl/Query.h>

namespace uking::query {

CheckActorAction::CheckActorAction(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckActorAction::~CheckActorAction() = default;

// FIXME: implement
int CheckActorAction::doQuery() {
    return -1;
}

void CheckActorAction::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "ActionName");
}

void CheckActorAction::loadParams() {
    getDynamicParam(&mActionName, "ActionName");
}

}  // namespace uking::query
