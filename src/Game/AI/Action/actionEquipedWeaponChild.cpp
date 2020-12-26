#include "Game/AI/Action/actionEquipedWeaponChild.h"

namespace uking::action {

EquipedWeaponChild::EquipedWeaponChild(const InitArg& arg) : BindAction(arg) {}

EquipedWeaponChild::~EquipedWeaponChild() = default;

bool EquipedWeaponChild::init_(sead::Heap* heap) {
    return BindAction::init_(heap);
}

void EquipedWeaponChild::enter_(ksys::act::ai::InlineParamPack* params) {
    BindAction::enter_(params);
}

void EquipedWeaponChild::leave_() {
    BindAction::leave_();
}

void EquipedWeaponChild::loadParams_() {
    BindAction::loadParams_();
    getStaticParam(&mIsChangeScale_s, "IsChangeScale");
}

void EquipedWeaponChild::calc_() {
    BindAction::calc_();
}

}  // namespace uking::action
