#include "Game/AI/Action/actionForkToggleWeaponXLinkSleep.h"

namespace uking::action {

ForkToggleWeaponXLinkSleep::ForkToggleWeaponXLinkSleep(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkToggleWeaponXLinkSleep::~ForkToggleWeaponXLinkSleep() = default;

bool ForkToggleWeaponXLinkSleep::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkToggleWeaponXLinkSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkToggleWeaponXLinkSleep::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkToggleWeaponXLinkSleep::loadParams_() {
    getStaticParam(&mToggle_s, "Toggle");
}

void ForkToggleWeaponXLinkSleep::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
