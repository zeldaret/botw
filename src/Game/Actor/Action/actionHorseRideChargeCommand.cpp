#include "Game/Actor/Action/actionHorseRideChargeCommand.h"

namespace uking::action {

HorseRideChargeCommand::HorseRideChargeCommand(const InitArg& arg) : HorseRideSetGearCommand(arg) {}

HorseRideChargeCommand::~HorseRideChargeCommand() = default;

bool HorseRideChargeCommand::init_(sead::Heap* heap) {
    return HorseRideSetGearCommand::init_(heap);
}

void HorseRideChargeCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideSetGearCommand::enter_(params);
}

void HorseRideChargeCommand::leave_() {
    HorseRideSetGearCommand::leave_();
}

void HorseRideChargeCommand::loadParams_() {
    HorseRideSetGearCommand::loadParams_();
}

void HorseRideChargeCommand::calc_() {
    HorseRideSetGearCommand::calc_();
}

}  // namespace uking::action
