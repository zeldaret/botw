#include "Game/AI/AI/aiLynelRepeatAttack.h"

namespace uking::ai {

LynelRepeatAttack::LynelRepeatAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelRepeatAttack::~LynelRepeatAttack() = default;

bool LynelRepeatAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelRepeatAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelRepeatAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelRepeatAttack::loadParams_() {
    getStaticParam(&mAttackNum_s, "AttackNum");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
