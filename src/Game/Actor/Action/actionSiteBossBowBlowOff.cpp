#include "Game/Actor/Action/actionSiteBossBowBlowOff.h"

namespace uking::action {

SiteBossBowBlowOff::SiteBossBowBlowOff(const InitArg& arg) : LastBossBlowOff(arg) {}

SiteBossBowBlowOff::~SiteBossBowBlowOff() = default;

bool SiteBossBowBlowOff::init_(sead::Heap* heap) {
    return LastBossBlowOff::init_(heap);
}

void SiteBossBowBlowOff::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossBlowOff::enter_(params);
}

void SiteBossBowBlowOff::leave_() {
    LastBossBlowOff::leave_();
}

void SiteBossBowBlowOff::loadParams_() {
    LastBossBlowOff::loadParams_();
    getStaticParam(&mAddForceRecoverTime_s, "AddForceRecoverTime");
    getStaticParam(&mIsRemoveCharacterController_s, "IsRemoveCharacterController");
    getStaticParam(&mForceRecoverDist_s, "ForceRecoverDist");
    getStaticParam(&mForceRecoverOffset_s, "ForceRecoverOffset");
}

void SiteBossBowBlowOff::calc_() {
    LastBossBlowOff::calc_();
}

}  // namespace uking::action
