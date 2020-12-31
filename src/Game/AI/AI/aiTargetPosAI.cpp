#include "Game/AI/AI/aiTargetPosAI.h"

namespace uking::ai {

TargetPosAI::TargetPosAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetPosAI::~TargetPosAI() = default;

bool TargetPosAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetPosAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetPosAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetPosAI::loadParams_() {
    getStaticParam(&mOnEnterOnly_s, "OnEnterOnly");
}

}  // namespace uking::ai
