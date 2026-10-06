#include "Game/Actor/AI/aiAppearFromTarget.h"

namespace uking::ai {

AppearFromTarget::AppearFromTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AppearFromTarget::~AppearFromTarget() = default;

bool AppearFromTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AppearFromTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AppearFromTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AppearFromTarget::loadParams_() {
    getStaticParam(&mDist_s, "Dist");
    getStaticParam(&mTeraDist_s, "TeraDist");
    getMapUnitParam(&mNearCreateAppearID_m, "NearCreateAppearID");
    getAITreeVariable(&mIsStopFallCheck_a, "IsStopFallCheck");
}

}  // namespace uking::ai
