#include "Game/Actor/AI/aiTargetLastAttackedPos.h"

namespace uking::ai {

TargetLastAttackedPos::TargetLastAttackedPos(const InitArg& arg) : TargetActorPos(arg) {}

TargetLastAttackedPos::~TargetLastAttackedPos() = default;

bool TargetLastAttackedPos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetLastAttackedPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetLastAttackedPos::leave_() {
    TargetActorPos::leave_();
}

void TargetLastAttackedPos::loadParams_() {
    TargetActorPos::loadParams_();
}

}  // namespace uking::ai
