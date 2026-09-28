#include "Game/Actor/Action/actionHorseRideSetGearCommand.h"

namespace uking::action {

HorseRideSetGearCommand::HorseRideSetGearCommand(const InitArg& arg) : HorseRideCommand(arg) {}

HorseRideSetGearCommand::~HorseRideSetGearCommand() = default;

bool HorseRideSetGearCommand::init_(sead::Heap* heap) {
    return HorseRideCommand::init_(heap);
}

void HorseRideSetGearCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideCommand::enter_(params);
}

void HorseRideSetGearCommand::leave_() {
    HorseRideCommand::leave_();
}

void HorseRideSetGearCommand::loadParams_() {
    HorseRideCommand::loadParams_();
    getStaticParam(&mGear_s, "Gear");
}

void HorseRideSetGearCommand::calc_() {
    HorseRideCommand::calc_();
}

}  // namespace uking::action
