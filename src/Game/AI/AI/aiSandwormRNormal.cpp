#include "Game/AI/AI/aiSandwormRNormal.h"

namespace uking::ai {

SandwormRNormal::SandwormRNormal(const InitArg& arg) : SandwormNormal(arg) {}

SandwormRNormal::~SandwormRNormal() = default;

bool SandwormRNormal::init_(sead::Heap* heap) {
    return SandwormNormal::init_(heap);
}

void SandwormRNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    SandwormNormal::enter_(params);
}

void SandwormRNormal::leave_() {
    SandwormNormal::leave_();
}

void SandwormRNormal::loadParams_() {
    SandwormNormal::loadParams_();
}

}  // namespace uking::ai
