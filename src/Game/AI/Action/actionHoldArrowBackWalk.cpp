#include "Game/AI/Action/actionHoldArrowBackWalk.h"

namespace uking::action {

HoldArrowBackWalk::HoldArrowBackWalk(const InitArg& arg) : BackWalkEx(arg) {}

void HoldArrowBackWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    BackWalkEx::enter_(params);
}

void HoldArrowBackWalk::leave_() {
    BackWalkEx::leave_();
}

void HoldArrowBackWalk::loadParams_() {
    BackWalkEx::loadParams_();
    getStaticParam(&mHoldWeaponIdx_s, "HoldWeaponIdx");
}

void HoldArrowBackWalk::calc_() {
    BackWalkEx::calc_();
}

}  // namespace uking::action
