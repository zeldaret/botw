#include "Game/AI/AI/aiWillBallRoot.h"

namespace uking::ai {

WillBallRoot::WillBallRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WillBallRoot::~WillBallRoot() = default;

bool WillBallRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WillBallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WillBallRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WillBallRoot::loadParams_() {
    getStaticParam(&mMagneLightningTime_s, "MagneLightningTime");
    getStaticParam(&mMinimizedTime_s, "MinimizedTime");
    getStaticParam(&mImmidiateLightningXZ_s, "ImmidiateLightningXZ");
    getStaticParam(&mImmidiateLightningY_s, "ImmidiateLightningY");
    getStaticParam(&mImmidiateLightningXZTarget_s, "ImmidiateLightningXZTarget");
    getStaticParam(&mImmidiateLightningYTarget_s, "ImmidiateLightningYTarget");
    getStaticParam(&mLightningTimeMinimizeDist_s, "LightningTimeMinimizeDist");
    getStaticParam(&mIsExplode_s, "IsExplode");
    getMapUnitParam(&mCount_m, "Count");
}

}  // namespace uking::ai
