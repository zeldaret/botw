#include "Game/Actor/Action/actionHorseRideArrowReload.h"

namespace uking::action {

HorseRideArrowReload::HorseRideArrowReload(const InitArg& arg) : HorseRideBase(arg) {}

HorseRideArrowReload::~HorseRideArrowReload() = default;

bool HorseRideArrowReload::init_(sead::Heap* heap) {
    return HorseRideBase::init_(heap);
}

void HorseRideArrowReload::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideBase::enter_(params);
}

void HorseRideArrowReload::leave_() {
    HorseRideBase::leave_();
}

void HorseRideArrowReload::loadParams_() {
    HorseRideBase::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void HorseRideArrowReload::calc_() {
    HorseRideBase::calc_();
}

}  // namespace uking::action
