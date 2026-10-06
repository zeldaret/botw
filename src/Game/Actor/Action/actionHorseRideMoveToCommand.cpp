#include "Game/Actor/Action/actionHorseRideMoveToCommand.h"

namespace uking::action {

HorseRideMoveToCommand::HorseRideMoveToCommand(const InitArg& arg) : HorseRideSetGearCommand(arg) {}

HorseRideMoveToCommand::~HorseRideMoveToCommand() = default;

bool HorseRideMoveToCommand::init_(sead::Heap* heap) {
    return HorseRideSetGearCommand::init_(heap);
}

void HorseRideMoveToCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideSetGearCommand::enter_(params);
}

void HorseRideMoveToCommand::leave_() {
    HorseRideSetGearCommand::leave_();
}

void HorseRideMoveToCommand::loadParams_() {
    HorseRideSetGearCommand::loadParams_();
}

void HorseRideMoveToCommand::calc_() {
    HorseRideSetGearCommand::calc_();
}

}  // namespace uking::action
