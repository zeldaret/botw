#include "Game/AI/Action/actionElectricDie.h"

namespace uking::action {

ElectricDie::ElectricDie(const InitArg& arg) : ElectricBlownOff(arg) {}

ElectricDie::~ElectricDie() = default;

void ElectricDie::enter_(ksys::act::ai::InlineParamPack* params) {
    ElectricBlownOff::enter_(params);
}

void ElectricDie::leave_() {
    ElectricBlownOff::leave_();
}

void ElectricDie::loadParams_() {
    ElectricBlownOff::loadParams_();
}

}  // namespace uking::action
