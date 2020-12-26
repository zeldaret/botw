#include "Game/AI/Action/actionDropBreakWeaponUnEquiped.h"

namespace uking::action {

DropBreakWeaponUnEquiped::DropBreakWeaponUnEquiped(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DropBreakWeaponUnEquiped::~DropBreakWeaponUnEquiped() = default;

bool DropBreakWeaponUnEquiped::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DropBreakWeaponUnEquiped::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DropBreakWeaponUnEquiped::leave_() {
    ksys::act::ai::Action::leave_();
}

void DropBreakWeaponUnEquiped::loadParams_() {
    getStaticParam(&mBoundNum_s, "BoundNum");
    getStaticParam(&mKillTimer_s, "KillTimer");
}

void DropBreakWeaponUnEquiped::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
