#include "Game/AI/AI/aiCircleMoveInWater.h"

namespace uking::ai {

CircleMoveInWater::CircleMoveInWater(const InitArg& arg) : CircleMoveInFluid(arg) {}

CircleMoveInWater::~CircleMoveInWater() = default;

bool CircleMoveInWater::init_(sead::Heap* heap) {
    return CircleMoveInFluid::init_(heap);
}

void CircleMoveInWater::enter_(ksys::act::ai::InlineParamPack* params) {
    CircleMoveInFluid::enter_(params);
}

void CircleMoveInWater::leave_() {
    CircleMoveInFluid::leave_();
}

void CircleMoveInWater::loadParams_() {
    CircleMoveInFluid::loadParams_();
    getStaticParam(&mAllowMoveWaterDepth_s, "AllowMoveWaterDepth");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
