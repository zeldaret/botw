#include "Game/AI/AI/aiAssassinMiddleDlcGrabAdapter.h"

namespace uking::ai {

AssassinMiddleDlcGrabAdapter::AssassinMiddleDlcGrabAdapter(const InitArg& arg)
    : TargetActorGrabAdapter(arg) {}

AssassinMiddleDlcGrabAdapter::~AssassinMiddleDlcGrabAdapter() = default;

bool AssassinMiddleDlcGrabAdapter::init_(sead::Heap* heap) {
    return TargetActorGrabAdapter::init_(heap);
}

void AssassinMiddleDlcGrabAdapter::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorGrabAdapter::enter_(params);
}

void AssassinMiddleDlcGrabAdapter::leave_() {
    TargetActorGrabAdapter::leave_();
}

void AssassinMiddleDlcGrabAdapter::loadParams_() {
    TargetActorGrabAdapter::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
