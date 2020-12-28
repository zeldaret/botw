#include "Game/AI/Action/actionHoldArrowWalk.h"

namespace uking::action {

HoldArrowWalk::HoldArrowWalk(const InitArg& arg) : MoveBase(arg) {}

HoldArrowWalk::~HoldArrowWalk() = default;

void HoldArrowWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
}

void HoldArrowWalk::leave_() {
    MoveBase::leave_();
}

void HoldArrowWalk::loadParams_() {
    MoveBase::loadParams_();
    getStaticParam(&mHoldWeaponIdx_s, "HoldWeaponIdx");
}

void HoldArrowWalk::calc_() {
    MoveBase::calc_();
}

}  // namespace uking::action
