#include "Game/AI/Action/actionGuardianMiniWait.h"

namespace uking::action {

GuardianMiniWait::GuardianMiniWait(const InitArg& arg) : Wait(arg) {}

GuardianMiniWait::~GuardianMiniWait() = default;

void GuardianMiniWait::enter_(ksys::act::ai::InlineParamPack* params) {
    Wait::enter_(params);
}

void GuardianMiniWait::loadParams_() {
    WaitBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mASSlotRight_s, "ASSlotRight");
    getStaticParam(&mASSlotLeft_s, "ASSlotLeft");
    getStaticParam(&mASSlotBack_s, "ASSlotBack");
    getDynamicParam(&mDynRightWeaponIdx_d, "DynRightWeaponIdx");
    getDynamicParam(&mDynLeftWeaponIdx_d, "DynLeftWeaponIdx");
    getDynamicParam(&mDynBackWeaponIdx_d, "DynBackWeaponIdx");
}

void GuardianMiniWait::calc_() {
    Wait::calc_();
}

}  // namespace uking::action
