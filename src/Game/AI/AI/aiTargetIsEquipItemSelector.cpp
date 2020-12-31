#include "Game/AI/AI/aiTargetIsEquipItemSelector.h"

namespace uking::ai {

TargetIsEquipItemSelector::TargetIsEquipItemSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetIsEquipItemSelector::~TargetIsEquipItemSelector() = default;

bool TargetIsEquipItemSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetIsEquipItemSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetIsEquipItemSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetIsEquipItemSelector::loadParams_() {
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
