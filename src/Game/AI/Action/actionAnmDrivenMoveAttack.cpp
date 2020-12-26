#include "Game/AI/Action/actionAnmDrivenMoveAttack.h"

namespace uking::action {

AnmDrivenMoveAttack::AnmDrivenMoveAttack(const InitArg& arg) : MoveByAnimeDriven(arg) {}

AnmDrivenMoveAttack::~AnmDrivenMoveAttack() = default;

bool AnmDrivenMoveAttack::init_(sead::Heap* heap) {
    return MoveByAnimeDriven::init_(heap);
}

void AnmDrivenMoveAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveByAnimeDriven::enter_(params);
}

void AnmDrivenMoveAttack::leave_() {
    MoveByAnimeDriven::leave_();
}

void AnmDrivenMoveAttack::loadParams_() {
    MoveByAnimeDriven::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mJustAvoidDist_s, "JustAvoidDist");
    getStaticParam(&mIsForceGuardBreak_s, "IsForceGuardBreak");
}

void AnmDrivenMoveAttack::calc_() {
    MoveByAnimeDriven::calc_();
}

}  // namespace uking::action
