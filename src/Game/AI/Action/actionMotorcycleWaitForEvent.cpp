#include "Game/AI/Action/actionMotorcycleWaitForEvent.h"

namespace uking::action {

MotorcycleWaitForEvent::MotorcycleWaitForEvent(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MotorcycleWaitForEvent::~MotorcycleWaitForEvent() = default;

bool MotorcycleWaitForEvent::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MotorcycleWaitForEvent::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MotorcycleWaitForEvent::leave_() {
    ksys::act::ai::Action::leave_();
}

void MotorcycleWaitForEvent::loadParams_() {}

void MotorcycleWaitForEvent::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
