#include "Game/AI/Action/actionElectricDie.h"

namespace uking::action {

ElectricDie::ElectricDie(const InitArg& arg) : ElectricBlownOff(arg) {}

ElectricDie::~ElectricDie() = default;

bool ElectricDie::init_(sead::Heap* heap) {
    return ElectricBlownOff::init_(heap);
}

void ElectricDie::enter_(ksys::act::ai::InlineParamPack* params) {
    ElectricBlownOff::enter_(params);
}

void ElectricDie::leave_() {
    ElectricBlownOff::leave_();
}

void ElectricDie::loadParams_() {
    ElectricBlownOff::loadParams_();
}

void ElectricDie::calc_() {
    ElectricBlownOff::calc_();
}

}  // namespace uking::action
