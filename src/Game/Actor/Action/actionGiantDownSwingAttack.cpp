#include "Game/Actor/Action/actionGiantDownSwingAttack.h"

namespace uking::action {

GiantDownSwingAttack::GiantDownSwingAttack(const InitArg& arg) : AttackWithAS(arg) {}

GiantDownSwingAttack::~GiantDownSwingAttack() = default;

bool GiantDownSwingAttack::init_(sead::Heap* heap) {
    return AttackWithAS::init_(heap);
}

void GiantDownSwingAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    AttackWithAS::enter_(params);
}

void GiantDownSwingAttack::leave_() {
    AttackWithAS::leave_();
}

void GiantDownSwingAttack::loadParams_() {
    AttackWithAS::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

void GiantDownSwingAttack::calc_() {
    AttackWithAS::calc_();
}

}  // namespace uking::action
