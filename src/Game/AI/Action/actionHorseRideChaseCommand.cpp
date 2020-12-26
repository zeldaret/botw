#include "Game/AI/Action/actionHorseRideChaseCommand.h"

namespace uking::action {

HorseRideChaseCommand::HorseRideChaseCommand(const InitArg& arg) : HorseRideMoveCommand(arg) {}

HorseRideChaseCommand::~HorseRideChaseCommand() = default;

bool HorseRideChaseCommand::init_(sead::Heap* heap) {
    return HorseRideMoveCommand::init_(heap);
}

void HorseRideChaseCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideMoveCommand::enter_(params);
}

void HorseRideChaseCommand::leave_() {
    HorseRideMoveCommand::leave_();
}

void HorseRideChaseCommand::loadParams_() {
    HorseRideMoveCommand::loadParams_();
    getStaticParam(&mChaseKeepDist_s, "ChaseKeepDist");
}

void HorseRideChaseCommand::calc_() {
    HorseRideMoveCommand::calc_();
}

}  // namespace uking::action
