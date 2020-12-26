#include "Game/AI/Action/actionNpcSwimNavMove.h"

namespace uking::action {

NpcSwimNavMove::NpcSwimNavMove(const InitArg& arg) : RandomMoveAction(arg) {}

NpcSwimNavMove::~NpcSwimNavMove() = default;

bool NpcSwimNavMove::init_(sead::Heap* heap) {
    return RandomMoveAction::init_(heap);
}

void NpcSwimNavMove::enter_(ksys::act::ai::InlineParamPack* params) {
    RandomMoveAction::enter_(params);
}

void NpcSwimNavMove::leave_() {
    RandomMoveAction::leave_();
}

void NpcSwimNavMove::loadParams_() {
    RandomMoveAction::loadParams_();
    getStaticParam(&mUpdateTargetPosInterval_s, "UpdateTargetPosInterval");
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

void NpcSwimNavMove::calc_() {
    RandomMoveAction::calc_();
}

}  // namespace uking::action
