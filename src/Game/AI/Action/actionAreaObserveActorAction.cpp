#include "Game/AI/Action/actionAreaObserveActorAction.h"

namespace uking::action {

AreaObserveActorAction::AreaObserveActorAction(const InitArg& arg) : AreaActorObserve(arg) {}

AreaObserveActorAction::~AreaObserveActorAction() = default;

bool AreaObserveActorAction::init_(sead::Heap* heap) {
    return AreaActorObserve::init_(heap);
}

void AreaObserveActorAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActorObserve::enter_(params);
}

void AreaObserveActorAction::leave_() {
    AreaActorObserve::leave_();
}

void AreaObserveActorAction::loadParams_() {
    getMapUnitParam(&mCount_m, "Count");
    getMapUnitParam(&mIsSendMessage_m, "IsSendMessage");
    getMapUnitParam(&mDefaultBasicSignal_m, "DefaultBasicSignal");
}

void AreaObserveActorAction::calc_() {
    AreaActorObserve::calc_();
}

}  // namespace uking::action
