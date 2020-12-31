#include "Game/AI/AI/aiTargetDynamicActorPos.h"

namespace uking::ai {

TargetDynamicActorPos::TargetDynamicActorPos(const InitArg& arg) : TargetPosAI(arg) {}

TargetDynamicActorPos::~TargetDynamicActorPos() = default;

bool TargetDynamicActorPos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetDynamicActorPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetDynamicActorPos::leave_() {
    TargetPosAI::leave_();
}

void TargetDynamicActorPos::loadParams_() {
    TargetPosAI::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
