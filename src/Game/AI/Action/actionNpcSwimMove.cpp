#include "Game/AI/Action/actionNpcSwimMove.h"

namespace uking::action {

NpcSwimMove::NpcSwimMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NpcSwimMove::~NpcSwimMove() = default;

bool NpcSwimMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NpcSwimMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NpcSwimMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void NpcSwimMove::loadParams_() {
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
    getStaticParam(&mIsClampRotVel_s, "IsClampRotVel");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mAddCalcStickX_s, "AddCalcStickX");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NpcSwimMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
