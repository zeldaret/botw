#include "Game/Actor/AI/aiTargetHomePos.h"

namespace uking::ai {

TargetHomePos::TargetHomePos(const InitArg& arg) : TargetActorPos(arg) {}

TargetHomePos::~TargetHomePos() = default;

bool TargetHomePos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetHomePos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetHomePos::leave_() {
    TargetActorPos::leave_();
}

void TargetHomePos::loadParams_() {
    TargetActorPos::loadParams_();
}

}  // namespace uking::ai
