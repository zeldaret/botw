#include "Game/AI/AI/aiWaitForTargetClose.h"

namespace uking::ai {

WaitForTargetClose::WaitForTargetClose(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WaitForTargetClose::~WaitForTargetClose() = default;

bool WaitForTargetClose::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WaitForTargetClose::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WaitForTargetClose::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WaitForTargetClose::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mRange_s, "Range");
    getStaticParam(&mFailRange_s, "FailRange");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
