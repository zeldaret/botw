#include "Game/AI/Action/actionHorseRideLookWait.h"

namespace uking::action {

HorseRideLookWait::HorseRideLookWait(const InitArg& arg) : HorseRide(arg) {}

HorseRideLookWait::~HorseRideLookWait() = default;

bool HorseRideLookWait::init_(sead::Heap* heap) {
    return HorseRide::init_(heap);
}

void HorseRideLookWait::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRide::enter_(params);
}

void HorseRideLookWait::leave_() {
    HorseRide::leave_();
}

void HorseRideLookWait::loadParams_() {
    HorseRide::loadParams_();
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void HorseRideLookWait::calc_() {
    HorseRide::calc_();
}

}  // namespace uking::action
