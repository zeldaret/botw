#include "Game/AI/AI/aiRideHorseAI.h"

namespace uking::ai {

RideHorseAI::RideHorseAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RideHorseAI::~RideHorseAI() = default;

bool RideHorseAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RideHorseAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RideHorseAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RideHorseAI::loadParams_() {
    getDynamicParam2(&mHasToPlayRidingOnAS_d, "HasToPlayRidingOnAS");
}

}  // namespace uking::ai
