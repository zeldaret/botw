#include "Game/AI/Action/actionEventRegisterToDeathConter.h"

namespace uking::action {

EventRegisterToDeathConter::EventRegisterToDeathConter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventRegisterToDeathConter::~EventRegisterToDeathConter() = default;

bool EventRegisterToDeathConter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventRegisterToDeathConter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventRegisterToDeathConter::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventRegisterToDeathConter::loadParams_() {
    getDynamicParam(&mIsInitializeData_d, "IsInitializeData");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mGameDataName_d, "GameDataName");
}

void EventRegisterToDeathConter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
