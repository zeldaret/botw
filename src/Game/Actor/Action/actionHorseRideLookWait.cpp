#include "Game/Actor/Action/actionHorseRideLookWait.h"

namespace uking::action {

HorseRideLookWait::HorseRideLookWait(const InitArg& arg) : HorseRideBase(arg) {}

HorseRideLookWait::~HorseRideLookWait() = default;

bool HorseRideLookWait::init_(sead::Heap* heap) {
    return HorseRideBase::init_(heap);
}

void HorseRideLookWait::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideBase::enter_(params);
}

void HorseRideLookWait::leave_() {
    HorseRideBase::leave_();
}

void HorseRideLookWait::loadParams_() {
    HorseRideBase::loadParams_();
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void HorseRideLookWait::calc_() {
    HorseRideBase::calc_();
}

}  // namespace uking::action
