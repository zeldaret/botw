#include "Game/Actor/Action/actionLastBossSwordWhirlSlashChargeBase.h"

namespace uking::action {

LastBossSwordWhirlSlashChargeBase::LastBossSwordWhirlSlashChargeBase(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

LastBossSwordWhirlSlashChargeBase::~LastBossSwordWhirlSlashChargeBase() = default;

bool LastBossSwordWhirlSlashChargeBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossSwordWhirlSlashChargeBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossSwordWhirlSlashChargeBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossSwordWhirlSlashChargeBase::loadParams_() {
    getStaticParam(&mChargeTime_s, "ChargeTime");
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LastBossSwordWhirlSlashChargeBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
