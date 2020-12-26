#include "Game/AI/Action/actionHorseRideDynSetGearCommand.h"

namespace uking::action {

HorseRideDynSetGearCommand::HorseRideDynSetGearCommand(const InitArg& arg)
    : HorseRideCommand(arg) {}

HorseRideDynSetGearCommand::~HorseRideDynSetGearCommand() = default;

bool HorseRideDynSetGearCommand::init_(sead::Heap* heap) {
    return HorseRideCommand::init_(heap);
}

void HorseRideDynSetGearCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideCommand::enter_(params);
}

void HorseRideDynSetGearCommand::leave_() {
    HorseRideCommand::leave_();
}

void HorseRideDynSetGearCommand::loadParams_() {
    HorseRideCommand::loadParams_();
    getDynamicParam(&mGear_d, "Gear");
}

void HorseRideDynSetGearCommand::calc_() {
    HorseRideCommand::calc_();
}

}  // namespace uking::action
