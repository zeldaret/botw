#include "Game/AI/Action/actionHorseRideAngryGear1Coomand.h"

namespace uking::action {

HorseRideAngryGear1Coomand::HorseRideAngryGear1Coomand(const InitArg& arg)
    : HorseRideCommand(arg) {}

HorseRideAngryGear1Coomand::~HorseRideAngryGear1Coomand() = default;

bool HorseRideAngryGear1Coomand::init_(sead::Heap* heap) {
    return HorseRideCommand::init_(heap);
}

void HorseRideAngryGear1Coomand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideCommand::enter_(params);
}

void HorseRideAngryGear1Coomand::leave_() {
    HorseRideCommand::leave_();
}

void HorseRideAngryGear1Coomand::loadParams_() {
    HorseRideCommand::loadParams_();
}

void HorseRideAngryGear1Coomand::calc_() {
    HorseRideCommand::calc_();
}

}  // namespace uking::action
