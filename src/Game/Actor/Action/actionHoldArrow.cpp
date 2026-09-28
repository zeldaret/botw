#include "Game/Actor/Action/actionHoldArrow.h"

namespace uking::action {

HoldArrow::HoldArrow(const InitArg& arg) : StopBase(arg) {}

void HoldArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void HoldArrow::leave_() {
    StopBase::leave_();
}

void HoldArrow::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

void HoldArrow::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
