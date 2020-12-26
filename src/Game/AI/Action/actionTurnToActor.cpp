#include "Game/AI/Action/actionTurnToActor.h"

namespace uking::action {

TurnToActor::TurnToActor(const InitArg& arg) : TurnToActorBase(arg) {}

TurnToActor::~TurnToActor() = default;

bool TurnToActor::init_(sead::Heap* heap) {
    return TurnToActorBase::init_(heap);
}

void TurnToActor::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnToActorBase::enter_(params);
}

void TurnToActor::leave_() {
    TurnToActorBase::leave_();
}

void TurnToActor::loadParams_() {
    TurnToActorBase::loadParams_();
    getDynamicParam(&mASSlot_d, "ASSlot");
    getDynamicParam(&mSequenceBank_d, "SequenceBank");
    getDynamicParam(&mIsIgnoreSame_d, "IsIgnoreSame");
    getDynamicParam(&mIsChangeable_d, "IsChangeable");
    getDynamicParam(&mASName_d, "ASName");
    getDynamicParam(&mDemoASName_d, "DemoASName");
}

void TurnToActor::calc_() {
    TurnToActorBase::calc_();
}

}  // namespace uking::action
