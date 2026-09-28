#include "Game/Actor/AI/aiAppearFromTargetFrontAfterChase.h"

namespace uking::ai {

AppearFromTargetFrontAfterChase::AppearFromTargetFrontAfterChase(const InitArg& arg)
    : AppearFromTarget(arg) {}

AppearFromTargetFrontAfterChase::~AppearFromTargetFrontAfterChase() = default;

void AppearFromTargetFrontAfterChase::enter_(ksys::act::ai::InlineParamPack* params) {
    AppearFromTarget::enter_(params);
}

void AppearFromTargetFrontAfterChase::leave_() {
    AppearFromTarget::leave_();
}

void AppearFromTargetFrontAfterChase::loadParams_() {
    AppearFromTarget::loadParams_();
    getStaticParam(&mAppearDist_s, "AppearDist");
}

}  // namespace uking::ai
