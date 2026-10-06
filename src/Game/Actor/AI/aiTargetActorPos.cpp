#include "Game/Actor/AI/aiTargetActorPos.h"

namespace uking::ai {

TargetActorPos::TargetActorPos(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetActorPos::~TargetActorPos() = default;

bool TargetActorPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetActorPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetActorPos::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetActorPos::loadParams_() {
    getStaticParam(&mOnEnterOnly_s, "OnEnterOnly");
}

}  // namespace uking::ai
