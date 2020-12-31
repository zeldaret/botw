#include "Game/AI/AI/aiFishSafeReturn.h"

namespace uking::ai {

FishSafeReturn::FishSafeReturn(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FishSafeReturn::~FishSafeReturn() = default;

bool FishSafeReturn::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FishSafeReturn::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void FishSafeReturn::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FishSafeReturn::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mDivePercent_s, "DivePercent");
    getStaticParam(&mAllowReturnThreatDist_s, "AllowReturnThreatDist");
    getDynamicParam(&mIsEscape_d, "IsEscape");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
