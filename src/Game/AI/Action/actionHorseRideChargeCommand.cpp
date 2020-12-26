#include "Game/AI/Action/actionHorseRideChargeCommand.h"

namespace uking::action {

HorseRideChargeCommand::HorseRideChargeCommand(const InitArg& arg) : HorseRideMoveCommand(arg) {}

HorseRideChargeCommand::~HorseRideChargeCommand() = default;

bool HorseRideChargeCommand::init_(sead::Heap* heap) {
    return HorseRideMoveCommand::init_(heap);
}

void HorseRideChargeCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideMoveCommand::enter_(params);
}

void HorseRideChargeCommand::leave_() {
    HorseRideMoveCommand::leave_();
}

void HorseRideChargeCommand::loadParams_() {
    HorseRideMoveCommand::loadParams_();
}

void HorseRideChargeCommand::calc_() {
    HorseRideMoveCommand::calc_();
}

}  // namespace uking::action
