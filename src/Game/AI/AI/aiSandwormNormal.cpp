#include "Game/AI/AI/aiSandwormNormal.h"

namespace uking::ai {

SandwormNormal::SandwormNormal(const InitArg& arg) : SandwormNormalBase(arg) {}

SandwormNormal::~SandwormNormal() = default;

bool SandwormNormal::init_(sead::Heap* heap) {
    return SandwormNormalBase::init_(heap);
}

void SandwormNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    SandwormNormalBase::enter_(params);
}

void SandwormNormal::leave_() {
    SandwormNormalBase::leave_();
}

void SandwormNormal::loadParams_() {
    SandwormNormalBase::loadParams_();
}

}  // namespace uking::ai
