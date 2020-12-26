#include "Game/AI/Action/actionAnmDrivenSpeedBackWalk.h"

namespace uking::action {

AnmDrivenSpeedBackWalk::AnmDrivenSpeedBackWalk(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnmDrivenSpeedBackWalk::~AnmDrivenSpeedBackWalk() = default;

bool AnmDrivenSpeedBackWalk::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnmDrivenSpeedBackWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AnmDrivenSpeedBackWalk::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnmDrivenSpeedBackWalk::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mRotAddRatio_s, "RotAddRatio");
    getStaticParam(&mFinishDist_s, "FinishDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AnmDrivenSpeedBackWalk::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
