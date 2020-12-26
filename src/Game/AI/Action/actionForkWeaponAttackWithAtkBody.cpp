#include "Game/AI/Action/actionForkWeaponAttackWithAtkBody.h"

namespace uking::action {

ForkWeaponAttackWithAtkBody::ForkWeaponAttackWithAtkBody(const InitArg& arg)
    : ForkWeaponAttack(arg) {}

ForkWeaponAttackWithAtkBody::~ForkWeaponAttackWithAtkBody() = default;

bool ForkWeaponAttackWithAtkBody::init_(sead::Heap* heap) {
    return ForkWeaponAttack::init_(heap);
}

void ForkWeaponAttackWithAtkBody::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkWeaponAttack::enter_(params);
}

void ForkWeaponAttackWithAtkBody::leave_() {
    ForkWeaponAttack::leave_();
}

void ForkWeaponAttackWithAtkBody::loadParams_() {
    ForkWeaponAttack::loadParams_();
    getStaticParam(&mAtkBodyName_s, "AtkBodyName");
}

void ForkWeaponAttackWithAtkBody::calc_() {
    ForkWeaponAttack::calc_();
}

}  // namespace uking::action
