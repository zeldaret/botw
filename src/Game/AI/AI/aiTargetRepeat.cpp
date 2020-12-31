#include "Game/AI/AI/aiTargetRepeat.h"

namespace uking::ai {

TargetRepeat::TargetRepeat(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetRepeat::~TargetRepeat() = default;

bool TargetRepeat::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetRepeat::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetRepeat::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetRepeat::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
