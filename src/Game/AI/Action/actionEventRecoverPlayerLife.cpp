#include "Game/AI/Action/actionEventRecoverPlayerLife.h"

namespace uking::action {

EventRecoverPlayerLife::EventRecoverPlayerLife(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventRecoverPlayerLife::~EventRecoverPlayerLife() = default;

bool EventRecoverPlayerLife::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventRecoverPlayerLife::loadParams_() {}

}  // namespace uking::action
