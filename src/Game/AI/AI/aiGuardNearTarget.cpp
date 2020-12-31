#include "Game/AI/AI/aiGuardNearTarget.h"

namespace uking::ai {

GuardNearTarget::GuardNearTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardNearTarget::~GuardNearTarget() = default;

bool GuardNearTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GuardNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardNearTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardNearTarget::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mGuardStartDist_s, "GuardStartDist");
    getStaticParam(&mGuardEndDist_s, "GuardEndDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
