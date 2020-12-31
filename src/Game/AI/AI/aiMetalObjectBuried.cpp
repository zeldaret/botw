#include "Game/AI/AI/aiMetalObjectBuried.h"

namespace uking::ai {

MetalObjectBuried::MetalObjectBuried(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MetalObjectBuried::~MetalObjectBuried() = default;

bool MetalObjectBuried::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MetalObjectBuried::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MetalObjectBuried::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MetalObjectBuried::loadParams_() {
    getStaticParam(&mPullOutSpeed_s, "PullOutSpeed");
    getStaticParam(&mCheckGroundRadiusScale_s, "CheckGroundRadiusScale");
    getStaticParam(&mIsIgnoreResistanceArea_s, "IsIgnoreResistanceArea");
    getStaticParam(&mIsCheckGrabYPosFix_s, "IsCheckGrabYPosFix");
    getStaticParam(&mIsCheckSelfY_s, "IsCheckSelfY");
    getMapUnitParam(&mIsInGround_m, "IsInGround");
    getMapUnitParam(&mEnableRevival_m, "EnableRevival");
}

}  // namespace uking::ai
