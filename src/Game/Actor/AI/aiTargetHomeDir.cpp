#include "Game/Actor/AI/aiTargetHomeDir.h"

namespace uking::ai {

TargetHomeDir::TargetHomeDir(const InitArg& arg) : TargetActorPos(arg) {}

TargetHomeDir::~TargetHomeDir() = default;

bool TargetHomeDir::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetHomeDir::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetHomeDir::leave_() {
    TargetActorPos::leave_();
}

void TargetHomeDir::loadParams_() {
    TargetActorPos::loadParams_();
}

}  // namespace uking::ai
