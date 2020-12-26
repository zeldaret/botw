#include "Game/AI/Action/actionAirOctaWoodBridge.h"

namespace uking::action {

AirOctaWoodBridge::AirOctaWoodBridge(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AirOctaWoodBridge::~AirOctaWoodBridge() = default;

bool AirOctaWoodBridge::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AirOctaWoodBridge::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AirOctaWoodBridge::leave_() {
    ksys::act::ai::Action::leave_();
}

void AirOctaWoodBridge::loadParams_() {}

void AirOctaWoodBridge::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
