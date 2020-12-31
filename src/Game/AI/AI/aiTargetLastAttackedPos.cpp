#include "Game/AI/AI/aiTargetLastAttackedPos.h"

namespace uking::ai {

TargetLastAttackedPos::TargetLastAttackedPos(const InitArg& arg) : TargetPosAI(arg) {}

TargetLastAttackedPos::~TargetLastAttackedPos() = default;

bool TargetLastAttackedPos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetLastAttackedPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetLastAttackedPos::leave_() {
    TargetPosAI::leave_();
}

void TargetLastAttackedPos::loadParams_() {
    TargetPosAI::loadParams_();
}

}  // namespace uking::ai
