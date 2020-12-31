#include "Game/AI/AI/aiTargetPosOffset.h"

namespace uking::ai {

TargetPosOffset::TargetPosOffset(const InitArg& arg) : TargetPosAI(arg) {}

TargetPosOffset::~TargetPosOffset() = default;

bool TargetPosOffset::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetPosOffset::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetPosOffset::leave_() {
    TargetPosAI::leave_();
}

void TargetPosOffset::loadParams_() {
    TargetPosAI::loadParams_();
    getStaticParam(&mDir_s, "Dir");
    getStaticParam(&mOffset_s, "Offset");
    getStaticParam(&mMinDist_s, "MinDist");
    getStaticParam(&mSideDist_s, "SideDist");
    getStaticParam(&mIsRandSide_s, "IsRandSide");
}

}  // namespace uking::ai
