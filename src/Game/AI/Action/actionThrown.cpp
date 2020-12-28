#include "Game/AI/Action/actionThrown.h"

namespace uking::action {

Thrown::Thrown(const InitArg& arg) : ActionEx(arg) {}

Thrown::~Thrown() = default;

void Thrown::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void Thrown::leave_() {
    ActionEx::leave_();
}

void Thrown::loadParams_() {
    getStaticParam(&mReactionLevel_s, "ReactionLevel");
    getStaticParam(&mIsForceOnly_s, "IsForceOnly");
    getStaticParam(&mIsOnImpact_s, "IsOnImpact");
    getStaticParam(&mAS_s, "AS");
    getStaticParam(&mThrownKey_s, "ThrownKey");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getDynamicParam(&mPower_d, "Power");
    getDynamicParam(&mIsShootByPlayer_d, "IsShootByPlayer");
    getDynamicParam(&mTargetDir_d, "TargetDir");
}

void Thrown::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
