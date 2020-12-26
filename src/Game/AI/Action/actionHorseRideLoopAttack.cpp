#include "Game/AI/Action/actionHorseRideLoopAttack.h"

namespace uking::action {

HorseRideLoopAttack::HorseRideLoopAttack(const InitArg& arg) : HorseRide(arg) {}

HorseRideLoopAttack::~HorseRideLoopAttack() = default;

bool HorseRideLoopAttack::init_(sead::Heap* heap) {
    return HorseRide::init_(heap);
}

void HorseRideLoopAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRide::enter_(params);
}

void HorseRideLoopAttack::leave_() {
    HorseRide::leave_();
}

void HorseRideLoopAttack::loadParams_() {
    HorseRide::loadParams_();
    getStaticParam(&mLoopAttackTime_s, "LoopAttackTime");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mIsFinishByAtHit_s, "IsFinishByAtHit");
    getStaticParam(&mIsNoRodAttack_s, "IsNoRodAttack");
    getStaticParam(&mFinishAS_s, "FinishAS");
    getStaticParam(&mASName_s, "ASName");
}

void HorseRideLoopAttack::calc_() {
    HorseRide::calc_();
}

}  // namespace uking::action
