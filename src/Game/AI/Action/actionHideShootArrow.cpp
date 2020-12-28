#include "Game/AI/Action/actionHideShootArrow.h"

namespace uking::action {

HideShootArrow::HideShootArrow(const InitArg& arg) : ShootArrow(arg) {}

HideShootArrow::~HideShootArrow() = default;

void HideShootArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ShootArrow::enter_(params);
}

void HideShootArrow::leave_() {
    ShootArrow::leave_();
}

void HideShootArrow::loadParams_() {
    ShootArrow::loadParams_();
    getStaticParam(&mShootStartASName_s, "ShootStartASName");
    getStaticParam(&mShootASName_s, "ShootASName");
    getStaticParam(&mShootEndASName_s, "ShootEndASName");
    getStaticParam(&mLoopTime_s, "LoopTime");
}

void HideShootArrow::calc_() {
    ShootArrow::calc_();
}

}  // namespace uking::action
