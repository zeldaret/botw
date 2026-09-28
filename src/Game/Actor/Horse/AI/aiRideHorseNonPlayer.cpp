#include "Game/Actor/Horse/AI/aiRideHorseNonPlayer.h"

namespace uking::ai {

RideHorseNonPlayer::RideHorseNonPlayer(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RideHorseNonPlayer::~RideHorseNonPlayer() = default;

bool RideHorseNonPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RideHorseNonPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RideHorseNonPlayer::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RideHorseNonPlayer::loadParams_() {}

}  // namespace uking::ai
