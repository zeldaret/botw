#include "Game/AI/AI/aiSunazarashiRoot.h"

namespace uking::ai {

SunazarashiRoot::SunazarashiRoot(const InitArg& arg) : PreyRoot(arg) {}

SunazarashiRoot::~SunazarashiRoot() = default;

bool SunazarashiRoot::init_(sead::Heap* heap) {
    return PreyRoot::init_(heap);
}

void SunazarashiRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PreyRoot::enter_(params);
}

void SunazarashiRoot::leave_() {
    PreyRoot::leave_();
}

void SunazarashiRoot::loadParams_() {
    PreyRoot::loadParams_();
    getStaticParam(&mStunNoiseLevel_s, "StunNoiseLevel");
    getStaticParam(&mClashSpeed_s, "ClashSpeed");
    getStaticParam(&mClashAngle_s, "ClashAngle");
    getStaticParam(&mEnableHangAlways_s, "EnableHangAlways");
    getMapUnitParam(&mForbidSystemDeleteDistance_m, "ForbidSystemDeleteDistance");
    getAITreeVariable(&mSunazarashiReturnPos_a, "SunazarashiReturnPos");
}

}  // namespace uking::ai
