#include "Game/AI/AI/aiTargetMyUp.h"

namespace uking::ai {

TargetMyUp::TargetMyUp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetMyUp::~TargetMyUp() = default;

bool TargetMyUp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetMyUp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetMyUp::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetMyUp::loadParams_() {
    getStaticParam(&mEndHeight_s, "EndHeight");
}

}  // namespace uking::ai
