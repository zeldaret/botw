#include "Game/AI/Action/actionMotorcycleWait.h"

namespace uking::action {

MotorcycleWait::MotorcycleWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MotorcycleWait::~MotorcycleWait() = default;

bool MotorcycleWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MotorcycleWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MotorcycleWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void MotorcycleWait::loadParams_() {}

void MotorcycleWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
