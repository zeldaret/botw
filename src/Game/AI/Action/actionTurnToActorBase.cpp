#include "Game/AI/Action/actionTurnToActorBase.h"

namespace uking::action {

TurnToActorBase::TurnToActorBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TurnToActorBase::~TurnToActorBase() = default;

bool TurnToActorBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TurnToActorBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TurnToActorBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void TurnToActorBase::loadParams_() {}

void TurnToActorBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
