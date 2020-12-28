#include "Game/AI/Action/actionFlyingBalloonObserverTag.h"

namespace uking::action {

FlyingBalloonObserverTag::FlyingBalloonObserverTag(const InitArg& arg)
    : AreaObserveActorAction(arg) {}

FlyingBalloonObserverTag::~FlyingBalloonObserverTag() = default;

bool FlyingBalloonObserverTag::init_(sead::Heap* heap) {
    return AreaObserveActorAction::init_(heap);
}

void FlyingBalloonObserverTag::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaObserveActorAction::enter_(params);
}

void FlyingBalloonObserverTag::leave_() {
    AreaObserveActorAction::leave_();
}

void FlyingBalloonObserverTag::calc_() {
    AreaObserveActorAction::calc_();
}

}  // namespace uking::action
