#include "Game/Actor/AI/aiTargetDynamicActorPos.h"

namespace uking::ai {

TargetDynamicActorPos::TargetDynamicActorPos(const InitArg& arg) : TargetActorPos(arg) {}

TargetDynamicActorPos::~TargetDynamicActorPos() = default;

bool TargetDynamicActorPos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetDynamicActorPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetDynamicActorPos::leave_() {
    TargetActorPos::leave_();
}

void TargetDynamicActorPos::loadParams_() {
    TargetActorPos::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
