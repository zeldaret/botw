#include "Game/Actor/AI/aiInvincibleNearTargetBase.h"

namespace uking::ai {

InvincibleNearTargetBase::InvincibleNearTargetBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

InvincibleNearTargetBase::~InvincibleNearTargetBase() = default;

bool InvincibleNearTargetBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void InvincibleNearTargetBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void InvincibleNearTargetBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void InvincibleNearTargetBase::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mGuardStartDist_s, "GuardStartDist");
    getStaticParam(&mGuardEndDist_s, "GuardEndDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
