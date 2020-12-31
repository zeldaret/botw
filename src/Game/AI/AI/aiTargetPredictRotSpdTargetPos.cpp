#include "Game/AI/AI/aiTargetPredictRotSpdTargetPos.h"

namespace uking::ai {

TargetPredictRotSpdTargetPos::TargetPredictRotSpdTargetPos(const InitArg& arg) : TargetPosAI(arg) {}

TargetPredictRotSpdTargetPos::~TargetPredictRotSpdTargetPos() = default;

bool TargetPredictRotSpdTargetPos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetPredictRotSpdTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetPredictRotSpdTargetPos::leave_() {
    TargetPosAI::leave_();
}

void TargetPredictRotSpdTargetPos::loadParams_() {
    TargetPosAI::loadParams_();
    getStaticParam(&mAddSpeed_s, "AddSpeed");
}

}  // namespace uking::ai
