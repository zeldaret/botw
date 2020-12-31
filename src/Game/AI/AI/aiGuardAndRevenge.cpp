#include "Game/AI/AI/aiGuardAndRevenge.h"

namespace uking::ai {

GuardAndRevenge::GuardAndRevenge(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool GuardAndRevenge::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GuardAndRevenge::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardAndRevenge::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardAndRevenge::loadParams_() {
    getStaticParam(&mDrownDepth_s, "DrownDepth");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
