#include "Game/AI/Action/actionEventSetFixed.h"

namespace uking::action {

EventSetFixed::EventSetFixed(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetFixed::~EventSetFixed() = default;

bool EventSetFixed::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetFixed::loadParams_() {
    getAITreeVariable(&mIsChangeToFixedInDemo_a, "IsChangeToFixedInDemo");
}

}  // namespace uking::action
