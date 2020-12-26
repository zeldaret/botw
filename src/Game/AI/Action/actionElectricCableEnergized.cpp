#include "Game/AI/Action/actionElectricCableEnergized.h"

namespace uking::action {

ElectricCableEnergized::ElectricCableEnergized(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ElectricCableEnergized::~ElectricCableEnergized() = default;

bool ElectricCableEnergized::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ElectricCableEnergized::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ElectricCableEnergized::leave_() {
    ksys::act::ai::Action::leave_();
}

void ElectricCableEnergized::loadParams_() {}

void ElectricCableEnergized::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
