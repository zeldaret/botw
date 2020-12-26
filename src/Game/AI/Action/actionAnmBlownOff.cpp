#include "Game/AI/Action/actionAnmBlownOff.h"

namespace uking::action {

AnmBlownOff::AnmBlownOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnmBlownOff::~AnmBlownOff() = default;

bool AnmBlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnmBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AnmBlownOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnmBlownOff::loadParams_() {
    getStaticParam(&mOnGroundTime_s, "OnGroundTime");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mBlownHeight_s, "BlownHeight");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mWeaponDropSpeedXZ_s, "WeaponDropSpeedXZ");
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
    getStaticParam(&mIsFinishByAnm_s, "IsFinishByAnm");
    getStaticParam(&mIsWaitForAnmEnd_s, "IsWaitForAnmEnd");
    getStaticParam(&mIsItemDrop_s, "IsItemDrop");
    getStaticParam(&mIsFinishByWater_s, "IsFinishByWater");
    getStaticParam(&mUseKnockbackDir_s, "UseKnockbackDir");
    getStaticParam(&mAS_s, "AS");
}

void AnmBlownOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
