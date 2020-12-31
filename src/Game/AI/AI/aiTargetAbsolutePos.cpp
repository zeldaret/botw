#include "Game/AI/AI/aiTargetAbsolutePos.h"

namespace uking::ai {

TargetAbsolutePos::TargetAbsolutePos(const InitArg& arg) : TargetPosAI(arg) {}

TargetAbsolutePos::~TargetAbsolutePos() = default;

bool TargetAbsolutePos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetAbsolutePos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetAbsolutePos::leave_() {
    TargetPosAI::leave_();
}

void TargetAbsolutePos::loadParams_() {
    TargetPosAI::loadParams_();
    getStaticParam(&mTargetPos_s, "TargetPos");
}

}  // namespace uking::ai
