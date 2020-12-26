#include "Game/AI/Action/actionHorseRideTurnCommand.h"

namespace uking::action {

HorseRideTurnCommand::HorseRideTurnCommand(const InitArg& arg) : HorseRideCommand(arg) {}

HorseRideTurnCommand::~HorseRideTurnCommand() = default;

bool HorseRideTurnCommand::init_(sead::Heap* heap) {
    return HorseRideCommand::init_(heap);
}

void HorseRideTurnCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideCommand::enter_(params);
}

void HorseRideTurnCommand::leave_() {
    HorseRideCommand::leave_();
}

void HorseRideTurnCommand::loadParams_() {
    HorseRideCommand::loadParams_();
}

void HorseRideTurnCommand::calc_() {
    HorseRideCommand::calc_();
}

}  // namespace uking::action
