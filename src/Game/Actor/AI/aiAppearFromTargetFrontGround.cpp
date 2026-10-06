#include "Game/Actor/AI/aiAppearFromTargetFrontGround.h"

namespace uking::ai {

AppearFromTargetFrontGround::AppearFromTargetFrontGround(const InitArg& arg)
    : AppearFromTarget(arg) {}

AppearFromTargetFrontGround::~AppearFromTargetFrontGround() = default;

bool AppearFromTargetFrontGround::init_(sead::Heap* heap) {
    return AppearFromTarget::init_(heap);
}

void AppearFromTargetFrontGround::enter_(ksys::act::ai::InlineParamPack* params) {
    AppearFromTarget::enter_(params);
}

void AppearFromTargetFrontGround::leave_() {
    AppearFromTarget::leave_();
}

void AppearFromTargetFrontGround::loadParams_() {
    AppearFromTarget::loadParams_();
}

}  // namespace uking::ai
