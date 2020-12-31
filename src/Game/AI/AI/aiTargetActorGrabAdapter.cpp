#include "Game/AI/AI/aiTargetActorGrabAdapter.h"

namespace uking::ai {

TargetActorGrabAdapter::TargetActorGrabAdapter(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetActorGrabAdapter::~TargetActorGrabAdapter() = default;

bool TargetActorGrabAdapter::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetActorGrabAdapter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetActorGrabAdapter::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetActorGrabAdapter::loadParams_() {
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
