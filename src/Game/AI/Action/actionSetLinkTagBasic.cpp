#include "Game/AI/Action/actionSetLinkTagBasic.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SetLinkTagBasicAction::SetLinkTagBasicAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetLinkTagBasicAction::~SetLinkTagBasicAction() = default;

void SetLinkTagBasicAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*IsOn)
        mActor->emitBasicSigOn();
    else
        mActor->emitBasicSigOff();

    setFinished();
}

void SetLinkTagBasicAction::loadParams_() {
    getStaticParam(&IsOn, "IsOn");
}

}  // namespace uking::action
