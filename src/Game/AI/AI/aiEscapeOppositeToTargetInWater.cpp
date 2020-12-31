#include "Game/AI/AI/aiEscapeOppositeToTargetInWater.h"

namespace uking::ai {

EscapeOppositeToTargetInWater::EscapeOppositeToTargetInWater(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

EscapeOppositeToTargetInWater::~EscapeOppositeToTargetInWater() = default;

bool EscapeOppositeToTargetInWater::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EscapeOppositeToTargetInWater::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EscapeOppositeToTargetInWater::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EscapeOppositeToTargetInWater::loadParams_() {
    getStaticParam(&mRunAwayDistanceMax_s, "RunAwayDistanceMax");
    getStaticParam(&mAllowRandAngleVertical_s, "AllowRandAngleVertical");
    getStaticParam(&mAllowRandAngleHorizontal_s, "AllowRandAngleHorizontal");
    getStaticParam(&mDivePercent_s, "DivePercent");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
