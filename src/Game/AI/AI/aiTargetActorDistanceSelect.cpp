#include "Game/AI/AI/aiTargetActorDistanceSelect.h"

namespace uking::ai {

TargetActorDistanceSelect::TargetActorDistanceSelect(const InitArg& arg)
    : TargetDistanceSelect(arg) {}

TargetActorDistanceSelect::~TargetActorDistanceSelect() = default;

bool TargetActorDistanceSelect::init_(sead::Heap* heap) {
    return TargetDistanceSelect::init_(heap);
}

void TargetActorDistanceSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetDistanceSelect::enter_(params);
}

void TargetActorDistanceSelect::leave_() {
    TargetDistanceSelect::leave_();
}

void TargetActorDistanceSelect::loadParams_() {
    TargetDistanceSelect::loadParams_();
}

}  // namespace uking::ai
