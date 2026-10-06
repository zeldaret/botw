#include "Game/Actor/Action/actionHorseRideChaseCommand.h"

namespace uking::action {

HorseRideChaseCommand::HorseRideChaseCommand(const InitArg& arg) : HorseRideSetGearCommand(arg) {}

HorseRideChaseCommand::~HorseRideChaseCommand() = default;

bool HorseRideChaseCommand::init_(sead::Heap* heap) {
    return HorseRideSetGearCommand::init_(heap);
}

void HorseRideChaseCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideSetGearCommand::enter_(params);
}

void HorseRideChaseCommand::leave_() {
    HorseRideSetGearCommand::leave_();
}

void HorseRideChaseCommand::loadParams_() {
    HorseRideSetGearCommand::loadParams_();
    getStaticParam(&mChaseKeepDist_s, "ChaseKeepDist");
}

void HorseRideChaseCommand::calc_() {
    HorseRideSetGearCommand::calc_();
}

}  // namespace uking::action
