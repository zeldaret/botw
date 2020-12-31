#include "Game/AI/AI/aiAppearNearTarget.h"

namespace uking::ai {

AppearNearTarget::AppearNearTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AppearNearTarget::~AppearNearTarget() = default;

bool AppearNearTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AppearNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AppearNearTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AppearNearTarget::loadParams_() {
    getStaticParam(&mDist_s, "Dist");
    getStaticParam(&mTeraDist_s, "TeraDist");
    getMapUnitParam(&mNearCreateAppearID_m, "NearCreateAppearID");
    getAITreeVariable(&mIsStopFallCheck_a, "IsStopFallCheck");
}

}  // namespace uking::ai
