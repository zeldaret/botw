#include "Game/AI/Action/actionSiteBossSwordWhirlSlashCharge.h"

namespace uking::action {

SiteBossSwordWhirlSlashCharge::SiteBossSwordWhirlSlashCharge(const InitArg& arg)
    : SiteBossSwordWhirlSlashChargeBase(arg) {}

SiteBossSwordWhirlSlashCharge::~SiteBossSwordWhirlSlashCharge() = default;

bool SiteBossSwordWhirlSlashCharge::init_(sead::Heap* heap) {
    return SiteBossSwordWhirlSlashChargeBase::init_(heap);
}

void SiteBossSwordWhirlSlashCharge::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossSwordWhirlSlashChargeBase::enter_(params);
}

void SiteBossSwordWhirlSlashCharge::leave_() {
    SiteBossSwordWhirlSlashChargeBase::leave_();
}

void SiteBossSwordWhirlSlashCharge::loadParams_() {
    SiteBossSwordWhirlSlashChargeBase::loadParams_();
}

void SiteBossSwordWhirlSlashCharge::calc_() {
    SiteBossSwordWhirlSlashChargeBase::calc_();
}

}  // namespace uking::action
