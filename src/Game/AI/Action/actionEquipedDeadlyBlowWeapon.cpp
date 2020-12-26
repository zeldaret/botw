#include "Game/AI/Action/actionEquipedDeadlyBlowWeapon.h"

namespace uking::action {

EquipedDeadlyBlowWeapon::EquipedDeadlyBlowWeapon(const InitArg& arg) : EquipedAction(arg) {}

EquipedDeadlyBlowWeapon::~EquipedDeadlyBlowWeapon() = default;

bool EquipedDeadlyBlowWeapon::init_(sead::Heap* heap) {
    return EquipedAction::init_(heap);
}

void EquipedDeadlyBlowWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    EquipedAction::enter_(params);
}

void EquipedDeadlyBlowWeapon::leave_() {
    EquipedAction::leave_();
}

void EquipedDeadlyBlowWeapon::loadParams_() {
    EquipedAction::loadParams_();
}

void EquipedDeadlyBlowWeapon::calc_() {
    EquipedAction::calc_();
}

}  // namespace uking::action
