#include "Game/AI/AI/aiTargetKnockBackBasePos.h"

namespace uking::ai {

TargetKnockBackBasePos::TargetKnockBackBasePos(const InitArg& arg) : TargetPosAI(arg) {}

TargetKnockBackBasePos::~TargetKnockBackBasePos() = default;

bool TargetKnockBackBasePos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetKnockBackBasePos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetKnockBackBasePos::leave_() {
    TargetPosAI::leave_();
}

void TargetKnockBackBasePos::loadParams_() {
    TargetPosAI::loadParams_();
}

}  // namespace uking::ai
