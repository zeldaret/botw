#include "Game/AI/AI/aiTargetTargetPos.h"

namespace uking::ai {

TargetTargetPos::TargetTargetPos(const InitArg& arg) : TargetPosAI(arg) {}

TargetTargetPos::~TargetTargetPos() = default;

bool TargetTargetPos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetTargetPos::leave_() {
    TargetPosAI::leave_();
}

void TargetTargetPos::loadParams_() {
    TargetPosAI::loadParams_();
    getStaticParam(&mAddSpeed_s, "AddSpeed");
}

}  // namespace uking::ai
