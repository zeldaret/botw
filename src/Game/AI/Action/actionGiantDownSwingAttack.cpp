#include "Game/AI/Action/actionGiantDownSwingAttack.h"

namespace uking::action {

GiantDownSwingAttack::GiantDownSwingAttack(const InitArg& arg) : GiantAttackWithAS(arg) {}

GiantDownSwingAttack::~GiantDownSwingAttack() = default;

bool GiantDownSwingAttack::init_(sead::Heap* heap) {
    return GiantAttackWithAS::init_(heap);
}

void GiantDownSwingAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantAttackWithAS::enter_(params);
}

void GiantDownSwingAttack::leave_() {
    GiantAttackWithAS::leave_();
}

void GiantDownSwingAttack::loadParams_() {
    GiantAttackWithAS::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

void GiantDownSwingAttack::calc_() {
    GiantAttackWithAS::calc_();
}

}  // namespace uking::action
