#include "Game/Actor/AI/aiTargetPosAnchorOffsetTarget.h"

namespace uking::ai {

TargetPosAnchorOffsetTarget::TargetPosAnchorOffsetTarget(const InitArg& arg)
    : TargetActorPos(arg) {}

TargetPosAnchorOffsetTarget::~TargetPosAnchorOffsetTarget() = default;

bool TargetPosAnchorOffsetTarget::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetPosAnchorOffsetTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetPosAnchorOffsetTarget::leave_() {
    TargetActorPos::leave_();
}

void TargetPosAnchorOffsetTarget::loadParams_() {
    TargetActorPos::loadParams_();
    getStaticParam(&mDist_s, "Dist");
    getStaticParam(&mAnchorName_s, "AnchorName");
}

}  // namespace uking::ai
