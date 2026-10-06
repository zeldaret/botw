#include "Game/Actor/AI/aiTargetPredictRotSpdTargetPos.h"

namespace uking::ai {

TargetPredictRotSpdTargetPos::TargetPredictRotSpdTargetPos(const InitArg& arg)
    : TargetActorPos(arg) {}

TargetPredictRotSpdTargetPos::~TargetPredictRotSpdTargetPos() = default;

bool TargetPredictRotSpdTargetPos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetPredictRotSpdTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetPredictRotSpdTargetPos::leave_() {
    TargetActorPos::leave_();
}

void TargetPredictRotSpdTargetPos::loadParams_() {
    TargetActorPos::loadParams_();
    getStaticParam(&mAddSpeed_s, "AddSpeed");
}

}  // namespace uking::ai
