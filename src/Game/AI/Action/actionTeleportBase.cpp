#include "Game/AI/Action/actionTeleportBase.h"

namespace uking::action {

TeleportBase::TeleportBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TeleportBase::~TeleportBase() = default;

bool TeleportBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TeleportBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TeleportBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void TeleportBase::loadParams_() {
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mTimeRand_s, "TimeRand");
    getStaticParam(&mIsUseChangePos_s, "IsUseChangePos");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mEffectName_s, "EffectName");
    getStaticParam(&mIsLifeGageKeep_s, "IsLifeGageKeep");
}

void TeleportBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
