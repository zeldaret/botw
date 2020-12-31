#include "Game/AI/AI/aiTargetTypeSelector.h"

namespace uking::ai {

TargetTypeSelector::TargetTypeSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetTypeSelector::~TargetTypeSelector() = default;

bool TargetTypeSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetTypeSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetTypeSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetTypeSelector::loadParams_() {
    getAITreeVariable(&mIsTrgTargetChangeToPlayer_a, "IsTrgTargetChangeToPlayer");
}

}  // namespace uking::ai
