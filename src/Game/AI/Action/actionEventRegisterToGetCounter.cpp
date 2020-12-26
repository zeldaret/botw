#include "Game/AI/Action/actionEventRegisterToGetCounter.h"

namespace uking::action {

EventRegisterToGetCounter::EventRegisterToGetCounter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventRegisterToGetCounter::~EventRegisterToGetCounter() = default;

bool EventRegisterToGetCounter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventRegisterToGetCounter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventRegisterToGetCounter::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventRegisterToGetCounter::loadParams_() {
    getDynamicParam(&mIsInitializeData_d, "IsInitializeData");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mGameDataName_d, "GameDataName");
}

void EventRegisterToGetCounter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
