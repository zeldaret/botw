#include "Game/AI/AI/aiLynelAttackThroughMove.h"

namespace uking::ai {

LynelAttackThroughMove::LynelAttackThroughMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelAttackThroughMove::~LynelAttackThroughMove() = default;

bool LynelAttackThroughMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelAttackThroughMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelAttackThroughMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelAttackThroughMove::loadParams_() {
    getStaticParam(&mSideOffsetDirType_s, "SideOffsetDirType");
    getStaticParam(&mCliffFailTime_s, "CliffFailTime");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSideOffset_s, "SideOffset");
    getStaticParam(&mThroughDist_s, "ThroughDist");
    getStaticParam(&mAcceptableRadius_s, "AcceptableRadius");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
