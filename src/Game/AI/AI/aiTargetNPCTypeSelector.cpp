#include "Game/AI/AI/aiTargetNPCTypeSelector.h"

namespace uking::ai {

TargetNPCTypeSelector::TargetNPCTypeSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetNPCTypeSelector::~TargetNPCTypeSelector() = default;

bool TargetNPCTypeSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetNPCTypeSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetNPCTypeSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetNPCTypeSelector::loadParams_() {}

}  // namespace uking::ai
