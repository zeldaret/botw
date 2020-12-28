#include "Game/AI/Action/actionEventSetEnableGrass.h"

namespace uking::action {

EventSetEnableGrass::EventSetEnableGrass(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetEnableGrass::~EventSetEnableGrass() = default;

bool EventSetEnableGrass::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetEnableGrass::loadParams_() {
    getDynamicParam(&mEnable_d, "Enable");
}

}  // namespace uking::action
