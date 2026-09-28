#include "Game/Actor/Action/actionHorseRideCommand.h"

namespace uking::action {

HorseRideCommand::HorseRideCommand(const InitArg& arg) : HorseRideOneTimeCommandBase(arg) {}

HorseRideCommand::~HorseRideCommand() = default;

bool HorseRideCommand::init_(sead::Heap* heap) {
    return HorseRideOneTimeCommandBase::init_(heap);
}

void HorseRideCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideOneTimeCommandBase::enter_(params);
}

void HorseRideCommand::leave_() {
    HorseRideOneTimeCommandBase::leave_();
}

void HorseRideCommand::loadParams_() {
    HorseRideOneTimeCommandBase::loadParams_();
    getStaticParam(&mCommandTiming_s, "CommandTiming");
}

void HorseRideCommand::calc_() {
    HorseRideOneTimeCommandBase::calc_();
}

}  // namespace uking::action
