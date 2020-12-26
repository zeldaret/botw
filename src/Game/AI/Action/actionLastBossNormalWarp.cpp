#include "Game/AI/Action/actionLastBossNormalWarp.h"

namespace uking::action {

LastBossNormalWarp::LastBossNormalWarp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossNormalWarp::~LastBossNormalWarp() = default;

bool LastBossNormalWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossNormalWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossNormalWarp::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossNormalWarp::loadParams_() {
    getStaticParam(&mOffsetLength_s, "OffsetLength");
    getStaticParam(&mOffsetY_s, "OffsetY");
    getStaticParam(&mWarpTime_s, "WarpTime");
    getStaticParam(&mCheckShapeRadius_s, "CheckShapeRadius");
    getStaticParam(&mIsUseChangePos_s, "IsUseChangePos");
    getStaticParam(&mIsEscapeFromPlayer_s, "IsEscapeFromPlayer");
    getStaticParam(&mIsWarpAtGround_s, "IsWarpAtGround");
    getStaticParam(&mIsChasePlayer_s, "IsChasePlayer");
    getStaticParam(&mDisableGroundHit_s, "DisableGroundHit");
    getStaticParam(&mDisableAirWallHit_s, "DisableAirWallHit");
    getStaticParam(&mChaseDist_s, "ChaseDist");
    getStaticParam(&mChaseDistOffset_s, "ChaseDistOffset");
    getStaticParam(&mHomePosOffset_s, "HomePosOffset");
    getDynamicParam(&mIsReturnHome_d, "IsReturnHome");
    getDynamicParam(&mIsForceWarp_d, "IsForceWarp");
    getDynamicParam(&mIsPartsActorTgOn_d, "IsPartsActorTgOn");
    getDynamicParam(&mIsKeepDisableDraw_d, "IsKeepDisableDraw");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LastBossNormalWarp::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
