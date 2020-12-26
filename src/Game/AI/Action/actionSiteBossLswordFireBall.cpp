#include "Game/AI/Action/actionSiteBossLswordFireBall.h"

namespace uking::action {

SiteBossLswordFireBall::SiteBossLswordFireBall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossLswordFireBall::~SiteBossLswordFireBall() = default;

bool SiteBossLswordFireBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossLswordFireBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossLswordFireBall::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossLswordFireBall::loadParams_() {
    getStaticParam(&mAppearInterval_s, "AppearInterval");
    getStaticParam(&mBallAppearOffset_s, "BallAppearOffset");
    getStaticParam(&mFireBallScale_s, "FireBallScale");
    getStaticParam(&mIsShowChildDevice_s, "IsShowChildDevice");
    getStaticParam(&mWaitASName_s, "WaitASName");
    getDynamicParam(&mPartsName_d, "PartsName");
}

void SiteBossLswordFireBall::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
