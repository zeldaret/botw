#include "Game/AI/Action/actionSetInstEventFlag.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SetInstEventFlagAction::SetInstEventFlagAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetInstEventFlagAction::~SetInstEventFlagAction() = default;

}  // namespace uking::action
