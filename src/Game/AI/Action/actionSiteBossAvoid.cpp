#include "Game/AI/Action/actionSiteBossAvoid.h"

namespace uking::action {

SiteBossAvoid::SiteBossAvoid(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossAvoid::~SiteBossAvoid() = default;

bool SiteBossAvoid::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossAvoid::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossAvoid::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossAvoid::loadParams_() {
    getStaticParam(&mAvoidEndTime_s, "AvoidEndTime");
    getStaticParam(&mAvoidMoveSpeed_s, "AvoidMoveSpeed");
    getDynamicParam(&mAvoidDist_d, "AvoidDist");
    getDynamicParam(&mIsAvoidHorizon_d, "IsAvoidHorizon");
    getDynamicParam(&mIsSlerp_d, "IsSlerp");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mAvoidVec_d, "AvoidVec");
    getDynamicParam(&mPlayerPos_d, "PlayerPos");
}

void SiteBossAvoid::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
