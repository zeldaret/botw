#include "Game/Actor/Action/actionHorseRideViewWait.h"

namespace uking::action {

HorseRideViewWait::HorseRideViewWait(const InitArg& arg) : HorseRideBase(arg) {}

HorseRideViewWait::~HorseRideViewWait() = default;

bool HorseRideViewWait::init_(sead::Heap* heap) {
    return HorseRideBase::init_(heap);
}

void HorseRideViewWait::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideBase::enter_(params);
}

void HorseRideViewWait::leave_() {
    HorseRideBase::leave_();
}

void HorseRideViewWait::loadParams_() {
    HorseRideBase::loadParams_();
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void HorseRideViewWait::calc_() {
    HorseRideBase::calc_();
}

}  // namespace uking::action
