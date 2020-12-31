#include "Game/AI/AI/aiTargetLastAttackerPos.h"

namespace uking::ai {

TargetLastAttackerPos::TargetLastAttackerPos(const InitArg& arg) : TargetPosAI(arg) {}

TargetLastAttackerPos::~TargetLastAttackerPos() = default;

bool TargetLastAttackerPos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetLastAttackerPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetLastAttackerPos::leave_() {
    TargetPosAI::leave_();
}

void TargetLastAttackerPos::loadParams_() {
    TargetPosAI::loadParams_();
}

}  // namespace uking::ai
