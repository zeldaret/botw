#include "Game/AI/AI/aiTargetHomePos.h"

namespace uking::ai {

TargetHomePos::TargetHomePos(const InitArg& arg) : TargetPosAI(arg) {}

TargetHomePos::~TargetHomePos() = default;

bool TargetHomePos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetHomePos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetHomePos::leave_() {
    TargetPosAI::leave_();
}

void TargetHomePos::loadParams_() {
    TargetPosAI::loadParams_();
}

}  // namespace uking::ai
