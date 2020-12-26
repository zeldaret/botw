#include "Game/AI/Action/actionSiteBossBowBlowOff.h"

namespace uking::action {

SiteBossBowBlowOff::SiteBossBowBlowOff(const InitArg& arg) : SiteBossBlowOff(arg) {}

SiteBossBowBlowOff::~SiteBossBowBlowOff() = default;

bool SiteBossBowBlowOff::init_(sead::Heap* heap) {
    return SiteBossBlowOff::init_(heap);
}

void SiteBossBowBlowOff::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossBlowOff::enter_(params);
}

void SiteBossBowBlowOff::leave_() {
    SiteBossBlowOff::leave_();
}

void SiteBossBowBlowOff::loadParams_() {
    SiteBossBlowOff::loadParams_();
    getStaticParam(&mAddForceRecoverTime_s, "AddForceRecoverTime");
    getStaticParam(&mIsRemoveCharacterController_s, "IsRemoveCharacterController");
    getStaticParam(&mForceRecoverDist_s, "ForceRecoverDist");
    getStaticParam(&mForceRecoverOffset_s, "ForceRecoverOffset");
}

void SiteBossBowBlowOff::calc_() {
    SiteBossBlowOff::calc_();
}

}  // namespace uking::action
