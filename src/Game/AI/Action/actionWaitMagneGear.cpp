#include "Game/AI/Action/actionWaitMagneGear.h"

namespace uking::action {

WaitMagneGear::WaitMagneGear(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitMagneGear::~WaitMagneGear() = default;

bool WaitMagneGear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitMagneGear::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitMagneGear::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitMagneGear::loadParams_() {}

void WaitMagneGear::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
