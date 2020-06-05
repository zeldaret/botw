#include "Game/Action/actionSetLinkTagBasic.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SetLinkTagBasicAction::SetLinkTagBasicAction(const ksys::act::ai::ClassArg& arg)
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
