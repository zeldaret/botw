#include "Game/AI/AI/aiWolfLinkWarp.h"

namespace uking::ai {

WolfLinkWarp::WolfLinkWarp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkWarp::~WolfLinkWarp() = default;

bool WolfLinkWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WolfLinkWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WolfLinkWarp::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkWarp::loadParams_() {
    getStaticParam(&mNumCalcPerFrame_s, "NumCalcPerFrame");
    getStaticParam(&mFramesUntilFail_s, "FramesUntilFail");
    getStaticParam(&mTransitFrames_s, "TransitFrames");
    getStaticParam(&mWarpFromPlayerOffset_s, "WarpFromPlayerOffset");
    getStaticParam(&mInitialAngle_s, "InitialAngle");
    getStaticParam(&mAreaSearchRadius_s, "AreaSearchRadius");
    getStaticParam(&mAreaSearchCharacterRadius_s, "AreaSearchCharacterRadius");
    getStaticParam(&mAreaThreshold_s, "AreaThreshold");
    getDynamicParam(&mWarpType_d, "WarpType");
}

}  // namespace uking::ai
