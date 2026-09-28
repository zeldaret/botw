#include "Game/Actor/AI/aiTargetLastDamagedPos.h"

namespace uking::ai {

TargetLastDamagedPos::TargetLastDamagedPos(const InitArg& arg) : TargetActorPos(arg) {}

TargetLastDamagedPos::~TargetLastDamagedPos() = default;

bool TargetLastDamagedPos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetLastDamagedPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetLastDamagedPos::leave_() {
    TargetActorPos::leave_();
}

void TargetLastDamagedPos::loadParams_() {
    TargetActorPos::loadParams_();
}

}  // namespace uking::ai
