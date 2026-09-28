#include "Game/Actor/AI/aiSandwormNormal.h"

namespace uking::ai {

SandwormNormal::SandwormNormal(const InitArg& arg) : AwnSeal(arg) {}

SandwormNormal::~SandwormNormal() = default;

bool SandwormNormal::init_(sead::Heap* heap) {
    return AwnSeal::init_(heap);
}

void SandwormNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    AwnSeal::enter_(params);
}

void SandwormNormal::leave_() {
    AwnSeal::leave_();
}

void SandwormNormal::loadParams_() {
    AwnSeal::loadParams_();
}

}  // namespace uking::ai
