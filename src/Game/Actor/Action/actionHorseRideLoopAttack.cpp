#include "Game/Actor/Action/actionHorseRideLoopAttack.h"

namespace uking::action {

HorseRideLoopAttack::HorseRideLoopAttack(const InitArg& arg) : HorseRideBase(arg) {}

HorseRideLoopAttack::~HorseRideLoopAttack() = default;

bool HorseRideLoopAttack::init_(sead::Heap* heap) {
    return HorseRideBase::init_(heap);
}

void HorseRideLoopAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideBase::enter_(params);
}

void HorseRideLoopAttack::leave_() {
    HorseRideBase::leave_();
}

void HorseRideLoopAttack::loadParams_() {
    HorseRideBase::loadParams_();
    getStaticParam(&mLoopAttackTime_s, "LoopAttackTime");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mIsFinishByAtHit_s, "IsFinishByAtHit");
    getStaticParam(&mIsNoRodAttack_s, "IsNoRodAttack");
    getStaticParam(&mFinishAS_s, "FinishAS");
    getStaticParam(&mASName_s, "ASName");
}

void HorseRideLoopAttack::calc_() {
    HorseRideBase::calc_();
}

}  // namespace uking::action
