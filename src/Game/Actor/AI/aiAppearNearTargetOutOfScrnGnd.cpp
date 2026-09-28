#include "Game/Actor/AI/aiAppearNearTargetOutOfScrnGnd.h"

namespace uking::ai {

AppearNearTargetOutOfScrnGnd::AppearNearTargetOutOfScrnGnd(const InitArg& arg)
    : AppearFromTarget(arg) {}

AppearNearTargetOutOfScrnGnd::~AppearNearTargetOutOfScrnGnd() = default;

bool AppearNearTargetOutOfScrnGnd::init_(sead::Heap* heap) {
    return AppearFromTarget::init_(heap);
}

void AppearNearTargetOutOfScrnGnd::enter_(ksys::act::ai::InlineParamPack* params) {
    AppearFromTarget::enter_(params);
}

void AppearNearTargetOutOfScrnGnd::leave_() {
    AppearFromTarget::leave_();
}

void AppearNearTargetOutOfScrnGnd::loadParams_() {
    AppearFromTarget::loadParams_();
}

}  // namespace uking::ai
