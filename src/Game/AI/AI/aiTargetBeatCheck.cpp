#include "Game/AI/AI/aiTargetBeatCheck.h"

namespace uking::ai {

TargetBeatCheck::TargetBeatCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetBeatCheck::~TargetBeatCheck() = default;

bool TargetBeatCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetBeatCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetBeatCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetBeatCheck::loadParams_() {}

}  // namespace uking::ai
