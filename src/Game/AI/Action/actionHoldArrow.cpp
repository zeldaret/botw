#include "Game/AI/Action/actionHoldArrow.h"

namespace uking::action {

HoldArrow::HoldArrow(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

void HoldArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void HoldArrow::leave_() {
    ActionWithPosAngReduce::leave_();
}

void HoldArrow::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

void HoldArrow::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
