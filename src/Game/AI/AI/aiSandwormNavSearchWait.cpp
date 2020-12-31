#include "Game/AI/AI/aiSandwormNavSearchWait.h"

namespace uking::ai {

SandwormNavSearchWait::SandwormNavSearchWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormNavSearchWait::~SandwormNavSearchWait() = default;

bool SandwormNavSearchWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormNavSearchWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SandwormNavSearchWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SandwormNavSearchWait::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
