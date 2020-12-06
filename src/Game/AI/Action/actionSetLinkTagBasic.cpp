#include "Game/AI/Action/actionSetLinkTagBasic.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SetLinkTagBasicAction::SetLinkTagBasicAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SetLinkTagBasicAction::~SetLinkTagBasicAction() = default;

void SetLinkTagBasicAction::enter() {
    if (IsOn.value())
        mActor->emitBasicSigOn();
    else
        mActor->emitBasicSigOff();

    setFinished();
}

void SetLinkTagBasicAction::loadParams() {
    getParamStatic(&IsOn, "IsOn");
}

}  // namespace uking::action
