#include "Game/AI/Action/actionEventSetDynamic.h"

namespace uking::action {

EventSetDynamic::EventSetDynamic(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetDynamic::~EventSetDynamic() = default;

bool EventSetDynamic::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetDynamic::loadParams_() {
    getAITreeVariable(&mIsChangeToFixedInDemo_a, "IsChangeToFixedInDemo");
}

}  // namespace uking::action
