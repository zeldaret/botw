#include "Game/Actor/AI/aiTargetPosAnchorOffsetSelf.h"

namespace uking::ai {

TargetPosAnchorOffsetSelf::TargetPosAnchorOffsetSelf(const InitArg& arg) : TargetActorPos(arg) {}

TargetPosAnchorOffsetSelf::~TargetPosAnchorOffsetSelf() = default;

bool TargetPosAnchorOffsetSelf::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetPosAnchorOffsetSelf::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetPosAnchorOffsetSelf::leave_() {
    TargetActorPos::leave_();
}

void TargetPosAnchorOffsetSelf::loadParams_() {
    TargetActorPos::loadParams_();
    getStaticParam(&mDist_s, "Dist");
    getStaticParam(&mAnchorName_s, "AnchorName");
}

}  // namespace uking::ai
