#include "Game/AI/Action/actionSiteBossSwordWhirlSlashChargeBase.h"

namespace uking::action {

SiteBossSwordWhirlSlashChargeBase::SiteBossSwordWhirlSlashChargeBase(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossSwordWhirlSlashChargeBase::~SiteBossSwordWhirlSlashChargeBase() = default;

bool SiteBossSwordWhirlSlashChargeBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossSwordWhirlSlashChargeBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossSwordWhirlSlashChargeBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossSwordWhirlSlashChargeBase::loadParams_() {
    getStaticParam(&mChargeTime_s, "ChargeTime");
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SiteBossSwordWhirlSlashChargeBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
