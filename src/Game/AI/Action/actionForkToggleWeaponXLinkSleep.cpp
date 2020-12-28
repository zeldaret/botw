#include "Game/AI/Action/actionForkToggleWeaponXLinkSleep.h"

namespace uking::action {

ForkToggleWeaponXLinkSleep::ForkToggleWeaponXLinkSleep(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkToggleWeaponXLinkSleep::~ForkToggleWeaponXLinkSleep() = default;

void ForkToggleWeaponXLinkSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkToggleWeaponXLinkSleep::loadParams_() {
    getStaticParam(&mToggle_s, "Toggle");
}

}  // namespace uking::action
