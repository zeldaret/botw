#include "Game/AI/AI/aiTargetPosAnchorOffsetSelf.h"

namespace uking::ai {

TargetPosAnchorOffsetSelf::TargetPosAnchorOffsetSelf(const InitArg& arg) : TargetPosAI(arg) {}

TargetPosAnchorOffsetSelf::~TargetPosAnchorOffsetSelf() = default;

bool TargetPosAnchorOffsetSelf::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetPosAnchorOffsetSelf::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetPosAnchorOffsetSelf::leave_() {
    TargetPosAI::leave_();
}

void TargetPosAnchorOffsetSelf::loadParams_() {
    TargetPosAI::loadParams_();
    getStaticParam(&mDist_s, "Dist");
    getStaticParam(&mAnchorName_s, "AnchorName");
}

}  // namespace uking::ai
