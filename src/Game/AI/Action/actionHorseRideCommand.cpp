#include "Game/AI/Action/actionHorseRideCommand.h"

namespace uking::action {

HorseRideCommand::HorseRideCommand(const InitArg& arg) : HorseRideCommandBase(arg) {}

HorseRideCommand::~HorseRideCommand() = default;

bool HorseRideCommand::init_(sead::Heap* heap) {
    return HorseRideCommandBase::init_(heap);
}

void HorseRideCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideCommandBase::enter_(params);
}

void HorseRideCommand::leave_() {
    HorseRideCommandBase::leave_();
}

void HorseRideCommand::loadParams_() {
    HorseRideCommandBase::loadParams_();
    getStaticParam(&mCommandTiming_s, "CommandTiming");
}

void HorseRideCommand::calc_() {
    HorseRideCommandBase::calc_();
}

}  // namespace uking::action
