#include "Game/AI/AI/aiNonPlayerHorseRide.h"

namespace uking::ai {

NonPlayerHorseRide::NonPlayerHorseRide(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NonPlayerHorseRide::~NonPlayerHorseRide() = default;

bool NonPlayerHorseRide::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NonPlayerHorseRide::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NonPlayerHorseRide::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NonPlayerHorseRide::loadParams_() {}

}  // namespace uking::ai
