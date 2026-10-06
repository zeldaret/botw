#include "Game/Actor/AI/aiTargetKnockBackBasePos.h"

namespace uking::ai {

TargetKnockBackBasePos::TargetKnockBackBasePos(const InitArg& arg) : TargetActorPos(arg) {}

TargetKnockBackBasePos::~TargetKnockBackBasePos() = default;

bool TargetKnockBackBasePos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetKnockBackBasePos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetKnockBackBasePos::leave_() {
    TargetActorPos::leave_();
}

void TargetKnockBackBasePos::loadParams_() {
    TargetActorPos::loadParams_();
}

}  // namespace uking::ai
