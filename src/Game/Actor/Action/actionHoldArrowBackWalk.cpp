#include "Game/Actor/Action/actionHoldArrowBackWalk.h"

namespace uking::action {

HoldArrowBackWalk::HoldArrowBackWalk(const InitArg& arg) : NormalBackWalk(arg) {}

void HoldArrowBackWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    NormalBackWalk::enter_(params);
}

void HoldArrowBackWalk::leave_() {
    NormalBackWalk::leave_();
}

void HoldArrowBackWalk::loadParams_() {
    NormalBackWalk::loadParams_();
    getStaticParam(&mHoldWeaponIdx_s, "HoldWeaponIdx");
}

void HoldArrowBackWalk::calc_() {
    NormalBackWalk::calc_();
}

}  // namespace uking::action
