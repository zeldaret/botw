#include "Game/AI/AI/aiWaitNearTarget.h"

namespace uking::ai {

WaitNearTarget::WaitNearTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WaitNearTarget::~WaitNearTarget() = default;

bool WaitNearTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WaitNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WaitNearTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WaitNearTarget::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mStartCloseDistOffset_s, "StartCloseDistOffset");
    getStaticParam(&mOutDistOffset_s, "OutDistOffset");
    getStaticParam(&mIsCheckLineReachableForClose_s, "IsCheckLineReachableForClose");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
