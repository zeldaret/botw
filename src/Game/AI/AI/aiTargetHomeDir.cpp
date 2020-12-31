#include "Game/AI/AI/aiTargetHomeDir.h"

namespace uking::ai {

TargetHomeDir::TargetHomeDir(const InitArg& arg) : TargetPosAI(arg) {}

TargetHomeDir::~TargetHomeDir() = default;

bool TargetHomeDir::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetHomeDir::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetHomeDir::leave_() {
    TargetPosAI::leave_();
}

void TargetHomeDir::loadParams_() {
    TargetPosAI::loadParams_();
}

}  // namespace uking::ai
