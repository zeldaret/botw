#include "Game/Action/actionSetInstEventFlag.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SetInstEventFlagAction::SetInstEventFlagAction(const ksys::act::ai::ClassArg& arg)
    : ksys::act::ai::Action(arg) {}

SetInstEventFlagAction::~SetInstEventFlagAction() = default;

}  // namespace uking::action