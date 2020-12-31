#include "Game/AI/AI/aiGanonApproachOnWallRoot.h"

namespace uking::ai {

GanonApproachOnWallRoot::GanonApproachOnWallRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonApproachOnWallRoot::~GanonApproachOnWallRoot() = default;

bool GanonApproachOnWallRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonApproachOnWallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonApproachOnWallRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonApproachOnWallRoot::loadParams_() {
    getStaticParam(&mApproachTime_s, "ApproachTime");
    getStaticParam(&mMinDist_s, "MinDist");
    getStaticParam(&mMaxDist_s, "MaxDist");
    getStaticParam(&mFinDist_s, "FinDist");
    getStaticParam(&mIsInterpolateYUp_s, "IsInterpolateYUp");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
