#include "Game/AI/AI/aiViewWaitWithInstDynActor.h"

namespace uking::ai {

ViewWaitWithInstDynActor::ViewWaitWithInstDynActor(const InitArg& arg) : ViewWait(arg) {}

ViewWaitWithInstDynActor::~ViewWaitWithInstDynActor() = default;

bool ViewWaitWithInstDynActor::init_(sead::Heap* heap) {
    return ViewWait::init_(heap);
}

void ViewWaitWithInstDynActor::enter_(ksys::act::ai::InlineParamPack* params) {
    ViewWait::enter_(params);
}

void ViewWaitWithInstDynActor::leave_() {
    ViewWait::leave_();
}

void ViewWaitWithInstDynActor::loadParams_() {
    ViewWait::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
