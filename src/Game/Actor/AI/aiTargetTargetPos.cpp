#include "Game/Actor/AI/aiTargetTargetPos.h"

namespace uking::ai {

TargetTargetPos::TargetTargetPos(const InitArg& arg) : TargetActorPos(arg) {}

TargetTargetPos::~TargetTargetPos() = default;

bool TargetTargetPos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetTargetPos::leave_() {
    TargetActorPos::leave_();
}

void TargetTargetPos::loadParams_() {
    TargetActorPos::loadParams_();
    getStaticParam(&mAddSpeed_s, "AddSpeed");
}

}  // namespace uking::ai
