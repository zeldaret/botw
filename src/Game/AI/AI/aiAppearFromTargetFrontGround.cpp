#include "Game/AI/AI/aiAppearFromTargetFrontGround.h"

namespace uking::ai {

AppearFromTargetFrontGround::AppearFromTargetFrontGround(const InitArg& arg)
    : AppearNearTarget(arg) {}

AppearFromTargetFrontGround::~AppearFromTargetFrontGround() = default;

bool AppearFromTargetFrontGround::init_(sead::Heap* heap) {
    return AppearNearTarget::init_(heap);
}

void AppearFromTargetFrontGround::enter_(ksys::act::ai::InlineParamPack* params) {
    AppearNearTarget::enter_(params);
}

void AppearFromTargetFrontGround::leave_() {
    AppearNearTarget::leave_();
}

void AppearFromTargetFrontGround::loadParams_() {
    AppearNearTarget::loadParams_();
}

}  // namespace uking::ai
