#include "Game/AI/Action/actionDemoTurnToActor.h"

namespace uking::action {

DemoTurnToActor::DemoTurnToActor(const InitArg& arg) : TurnToActor(arg) {}

DemoTurnToActor::~DemoTurnToActor() = default;

bool DemoTurnToActor::init_(sead::Heap* heap) {
    return TurnToActor::init_(heap);
}

void DemoTurnToActor::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnToActor::enter_(params);
}

void DemoTurnToActor::leave_() {
    TurnToActor::leave_();
}

void DemoTurnToActor::loadParams_() {
    TurnToActor::loadParams_();
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

void DemoTurnToActor::calc_() {
    TurnToActor::calc_();
}

}  // namespace uking::action
