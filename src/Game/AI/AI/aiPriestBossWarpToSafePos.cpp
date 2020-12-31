#include "Game/AI/AI/aiPriestBossWarpToSafePos.h"

namespace uking::ai {

PriestBossWarpToSafePos::PriestBossWarpToSafePos(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossWarpToSafePos::~PriestBossWarpToSafePos() = default;

bool PriestBossWarpToSafePos::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossWarpToSafePos::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

void PriestBossWarpToSafePos::leave_() {
    PriestBossMode::leave_();
}

void PriestBossWarpToSafePos::loadParams_() {
    PriestBossMode::loadParams_();
    getStaticParam(&mOffsetY_s, "OffsetY");
    getStaticParam(&mOffsetZ_s, "OffsetZ");
    getAITreeVariable(&mIsActive_a, "IsActive");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
}

}  // namespace uking::ai
