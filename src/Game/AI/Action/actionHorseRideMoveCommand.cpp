#include "Game/AI/Action/actionHorseRideMoveCommand.h"

namespace uking::action {

HorseRideMoveCommand::HorseRideMoveCommand(const InitArg& arg) : HorseRideCommand(arg) {}

HorseRideMoveCommand::~HorseRideMoveCommand() = default;

bool HorseRideMoveCommand::init_(sead::Heap* heap) {
    return HorseRideCommand::init_(heap);
}

void HorseRideMoveCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideCommand::enter_(params);
}

void HorseRideMoveCommand::leave_() {
    HorseRideCommand::leave_();
}

void HorseRideMoveCommand::loadParams_() {
    HorseRideCommand::loadParams_();
    getStaticParam(&mGear_s, "Gear");
}

void HorseRideMoveCommand::calc_() {
    HorseRideCommand::calc_();
}

}  // namespace uking::action
