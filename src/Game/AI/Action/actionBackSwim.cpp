#include "Game/AI/Action/actionBackSwim.h"

namespace uking::action {

BackSwim::BackSwim(const InitArg& arg) : WaterFloatBase(arg) {}

BackSwim::~BackSwim() = default;

bool BackSwim::init_(sead::Heap* heap) {
    return WaterFloatBase::init_(heap);
}

void BackSwim::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatBase::enter_(params);
}

void BackSwim::leave_() {
    WaterFloatBase::leave_();
}

void BackSwim::loadParams_() {
    WaterFloatBase::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mRotAddRatio_s, "RotAddRatio");
    getStaticParam(&mFinishDist_s, "FinishDist");
    getStaticParam(&mDecelRatio_s, "DecelRatio");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mIsCheckCliff_s, "IsCheckCliff");
}

void BackSwim::calc_() {
    WaterFloatBase::calc_();
}

}  // namespace uking::action
