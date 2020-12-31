#include "Game/AI/AI/aiTargetPosOffsetFromMyPos.h"

namespace uking::ai {

TargetPosOffsetFromMyPos::TargetPosOffsetFromMyPos(const InitArg& arg) : TargetPosOffset(arg) {}

TargetPosOffsetFromMyPos::~TargetPosOffsetFromMyPos() = default;

bool TargetPosOffsetFromMyPos::init_(sead::Heap* heap) {
    return TargetPosOffset::init_(heap);
}

void TargetPosOffsetFromMyPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosOffset::enter_(params);
}

void TargetPosOffsetFromMyPos::leave_() {
    TargetPosOffset::leave_();
}

void TargetPosOffsetFromMyPos::loadParams_() {
    TargetPosOffset::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
