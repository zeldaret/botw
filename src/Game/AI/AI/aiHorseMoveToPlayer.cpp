#include "Game/AI/AI/aiHorseMoveToPlayer.h"

namespace uking::ai {

HorseMoveToPlayer::HorseMoveToPlayer(const InitArg& arg) : HorseFollow(arg) {}

HorseMoveToPlayer::~HorseMoveToPlayer() = default;

bool HorseMoveToPlayer::init_(sead::Heap* heap) {
    return HorseFollow::init_(heap);
}

void HorseMoveToPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseFollow::enter_(params);
}

void HorseMoveToPlayer::leave_() {
    HorseFollow::leave_();
}

void HorseMoveToPlayer::loadParams_() {
    HorseFollow::loadParams_();
    getStaticParam(&mDistanceSuccessEndIfInterrupted_s, "DistanceSuccessEndIfInterrupted");
    getStaticParam(&mDistanceResetGearInput_s, "DistanceResetGearInput");
}

}  // namespace uking::ai
