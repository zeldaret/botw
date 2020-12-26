#include "Game/AI/Action/actionHorseRideShoot.h"

namespace uking::action {

HorseRideShoot::HorseRideShoot(const InitArg& arg) : HorseRide(arg) {}

HorseRideShoot::~HorseRideShoot() = default;

bool HorseRideShoot::init_(sead::Heap* heap) {
    return HorseRide::init_(heap);
}

void HorseRideShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRide::enter_(params);
}

void HorseRideShoot::leave_() {
    HorseRide::leave_();
}

void HorseRideShoot::loadParams_() {
    HorseRide::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mOffsetRangeMin_s, "OffsetRangeMin");
    getStaticParam(&mOffsetRangeMax_s, "OffsetRangeMax");
    getStaticParam(&mOffsetRateByDist_s, "OffsetRateByDist");
    getStaticParam(&mOffsetRangeMinOutOfScreen_s, "OffsetRangeMinOutOfScreen");
    getStaticParam(&mOffsetRangeMaxOutOfScreen_s, "OffsetRangeMaxOutOfScreen");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void HorseRideShoot::calc_() {
    HorseRide::calc_();
}

}  // namespace uking::action
