#include "Game/AI/AI/aiAppearNearTargetOutOfScrnGnd.h"

namespace uking::ai {

AppearNearTargetOutOfScrnGnd::AppearNearTargetOutOfScrnGnd(const InitArg& arg)
    : AppearNearTarget(arg) {}

AppearNearTargetOutOfScrnGnd::~AppearNearTargetOutOfScrnGnd() = default;

bool AppearNearTargetOutOfScrnGnd::init_(sead::Heap* heap) {
    return AppearNearTarget::init_(heap);
}

void AppearNearTargetOutOfScrnGnd::enter_(ksys::act::ai::InlineParamPack* params) {
    AppearNearTarget::enter_(params);
}

void AppearNearTargetOutOfScrnGnd::leave_() {
    AppearNearTarget::leave_();
}

void AppearNearTargetOutOfScrnGnd::loadParams_() {
    AppearNearTarget::loadParams_();
}

}  // namespace uking::ai
