#include "Game/AI/AI/aiAirOctaReaction.h"

namespace uking::ai {

AirOctaReaction::AirOctaReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

AirOctaReaction::~AirOctaReaction() = default;

bool AirOctaReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void AirOctaReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

void AirOctaReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void AirOctaReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

}  // namespace uking::ai
