#include "Game/AI/Action/actionZoraSurfing.h"

namespace uking::action {

ZoraSurfing::ZoraSurfing(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ZoraSurfing::~ZoraSurfing() = default;

bool ZoraSurfing::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ZoraSurfing::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ZoraSurfing::leave_() {
    ksys::act::ai::Action::leave_();
}

void ZoraSurfing::loadParams_() {
    getStaticParam(&mRotRadPerSec_s, "RotRadPerSec");
    getStaticParam(&mWallHitTime_s, "WallHitTime");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinHeight_s, "FinHeight");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatRadius_s, "FloatRadius");
    getStaticParam(&mFloatCycleTime_s, "FloatCycleTime");
    getStaticParam(&mChangeDepthSpeed_s, "ChangeDepthSpeed");
    getStaticParam(&mOnRailDistance_s, "OnRailDistance");
    getStaticParam(&mFarDistance_s, "FarDistance");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mIsClampRotVel_s, "IsClampRotVel");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mASNameJump_s, "ASNameJump");
    getStaticParam(&mAddCalcStickX_s, "AddCalcStickX");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

void ZoraSurfing::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
