#include "Game/AI/AI/aiCircleMoveFlying.h"

namespace uking::ai {

CircleMoveFlying::CircleMoveFlying(const InitArg& arg) : CircleMoveInFluid(arg) {}

CircleMoveFlying::~CircleMoveFlying() = default;

bool CircleMoveFlying::init_(sead::Heap* heap) {
    return CircleMoveInFluid::init_(heap);
}

void CircleMoveFlying::enter_(ksys::act::ai::InlineParamPack* params) {
    CircleMoveInFluid::enter_(params);
}

void CircleMoveFlying::leave_() {
    CircleMoveInFluid::leave_();
}

void CircleMoveFlying::loadParams_() {
    CircleMoveInFluid::loadParams_();
    getStaticParam(&mIsCheckSafetyAreaRadius_s, "IsCheckSafetyAreaRadius");
    getStaticParam(&mIsUseHomePos_s, "IsUseHomePos");
}

}  // namespace uking::ai
