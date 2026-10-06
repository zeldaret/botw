#include "Game/Actor/AI/aiOffsetTargetPos.h"

namespace uking::ai {

OffsetTargetPos::OffsetTargetPos(const InitArg& arg) : TargetActorPos(arg) {}

OffsetTargetPos::~OffsetTargetPos() = default;

bool OffsetTargetPos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void OffsetTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void OffsetTargetPos::leave_() {
    TargetActorPos::leave_();
}

void OffsetTargetPos::loadParams_() {
    TargetActorPos::loadParams_();
    getStaticParam(&mDir_s, "Dir");
    getStaticParam(&mOffset_s, "Offset");
    getStaticParam(&mMinDist_s, "MinDist");
    getStaticParam(&mSideDist_s, "SideDist");
    getStaticParam(&mIsRandSide_s, "IsRandSide");
}

}  // namespace uking::ai
