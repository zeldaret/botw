#include "Game/AI/Action/actionHorseRideCancelCommand.h"

namespace uking::action {

HorseRideCancelCommand::HorseRideCancelCommand(const InitArg& arg) : HorseRideCommand(arg) {}

HorseRideCancelCommand::~HorseRideCancelCommand() = default;

bool HorseRideCancelCommand::init_(sead::Heap* heap) {
    return HorseRideCommand::init_(heap);
}

void HorseRideCancelCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideCommand::enter_(params);
}

void HorseRideCancelCommand::leave_() {
    HorseRideCommand::leave_();
}

void HorseRideCancelCommand::loadParams_() {
    HorseRideCommand::loadParams_();
}

void HorseRideCancelCommand::calc_() {
    HorseRideCommand::calc_();
}

}  // namespace uking::action
