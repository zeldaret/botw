#include "Game/AI/Action/actionSwarmDamagedBase.h"

namespace uking::action {

SwarmDamagedBase::SwarmDamagedBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SwarmDamagedBase::~SwarmDamagedBase() = default;

bool SwarmDamagedBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SwarmDamagedBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SwarmDamagedBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void SwarmDamagedBase::loadParams_() {
    getStaticParam(&mIgnoreHitGroundTime_s, "IgnoreHitGroundTime");
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mRiseSpeedMin_s, "RiseSpeedMin");
    getStaticParam(&mSubAccRateMin_s, "SubAccRateMin");
    getStaticParam(&mSubAccRateMax_s, "SubAccRateMax");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mIsCreateDeadActor_s, "IsCreateDeadActor");
    getMapUnitParam(&mSubUnitNum_m, "SubUnitNum");
    getMapUnitParam(&mPatternID_m, "PatternID");
}

void SwarmDamagedBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
