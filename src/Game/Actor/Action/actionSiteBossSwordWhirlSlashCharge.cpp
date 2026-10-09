#include "Game/Actor/Action/actionSiteBossSwordWhirlSlashCharge.h"

namespace uking::action {

SiteBossSwordWhirlSlashCharge::SiteBossSwordWhirlSlashCharge(const InitArg& arg)
    : LastBossSwordWhirlSlashChargeBase(arg) {}

SiteBossSwordWhirlSlashCharge::~SiteBossSwordWhirlSlashCharge() = default;

bool SiteBossSwordWhirlSlashCharge::init_(sead::Heap* heap) {
    return LastBossSwordWhirlSlashChargeBase::init_(heap);
}

void SiteBossSwordWhirlSlashCharge::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossSwordWhirlSlashChargeBase::enter_(params);
}

void SiteBossSwordWhirlSlashCharge::leave_() {
    LastBossSwordWhirlSlashChargeBase::leave_();
}

void SiteBossSwordWhirlSlashCharge::loadParams_() {
    LastBossSwordWhirlSlashChargeBase::loadParams_();
}

void SiteBossSwordWhirlSlashCharge::calc_() {
    LastBossSwordWhirlSlashChargeBase::calc_();
}

}  // namespace uking::action
