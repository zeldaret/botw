#include "Game/AI/Action/actionEventRegisterToDeathConter.h"

namespace uking::action {

EventRegisterToDeathConter::EventRegisterToDeathConter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventRegisterToDeathConter::~EventRegisterToDeathConter() = default;

bool EventRegisterToDeathConter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventRegisterToDeathConter::loadParams_() {
    getDynamicParam(&mIsInitializeData_d, "IsInitializeData");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mGameDataName_d, "GameDataName");
}

}  // namespace uking::action
