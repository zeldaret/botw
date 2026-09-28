#include "Game/Actor/AI/aiTargetLastAttackerPos.h"

namespace uking::ai {

TargetLastAttackerPos::TargetLastAttackerPos(const InitArg& arg) : TargetActorPos(arg) {}

TargetLastAttackerPos::~TargetLastAttackerPos() = default;

bool TargetLastAttackerPos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetLastAttackerPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetLastAttackerPos::leave_() {
    TargetActorPos::leave_();
}

void TargetLastAttackerPos::loadParams_() {
    TargetActorPos::loadParams_();
}

}  // namespace uking::ai
