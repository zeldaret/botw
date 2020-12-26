#include "Game/AI/Action/actionHorseRideStopCommand.h"

namespace uking::action {

HorseRideStopCommand::HorseRideStopCommand(const InitArg& arg) : HorseRideCommand(arg) {}

HorseRideStopCommand::~HorseRideStopCommand() = default;

bool HorseRideStopCommand::init_(sead::Heap* heap) {
    return HorseRideCommand::init_(heap);
}

void HorseRideStopCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideCommand::enter_(params);
}

void HorseRideStopCommand::leave_() {
    HorseRideCommand::leave_();
}

void HorseRideStopCommand::loadParams_() {
    HorseRideCommand::loadParams_();
}

void HorseRideStopCommand::calc_() {
    HorseRideCommand::calc_();
}

}  // namespace uking::action
