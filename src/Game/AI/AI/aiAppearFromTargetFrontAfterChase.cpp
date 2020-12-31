#include "Game/AI/AI/aiAppearFromTargetFrontAfterChase.h"

namespace uking::ai {

AppearFromTargetFrontAfterChase::AppearFromTargetFrontAfterChase(const InitArg& arg)
    : AppearNearTarget(arg) {}

AppearFromTargetFrontAfterChase::~AppearFromTargetFrontAfterChase() = default;

void AppearFromTargetFrontAfterChase::enter_(ksys::act::ai::InlineParamPack* params) {
    AppearNearTarget::enter_(params);
}

void AppearFromTargetFrontAfterChase::leave_() {
    AppearNearTarget::leave_();
}

void AppearFromTargetFrontAfterChase::loadParams_() {
    AppearNearTarget::loadParams_();
    getStaticParam(&mAppearDist_s, "AppearDist");
}

}  // namespace uking::ai
