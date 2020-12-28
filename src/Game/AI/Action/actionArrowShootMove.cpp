#include "Game/AI/Action/actionArrowShootMove.h"

namespace uking::action {

ArrowShootMove::ArrowShootMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ArrowShootMove::~ArrowShootMove() = default;

void ArrowShootMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ArrowShootMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void ArrowShootMove::loadParams_() {
    getDynamicParam(&mIsShootByPlayer_d, "IsShootByPlayer");
    getDynamicParam(&mFirstSpeed_d, "FirstSpeed");
    getDynamicParam(&mAccel_d, "Accel");
    getDynamicParam(&mAimSpeed_d, "AimSpeed");
    getDynamicParam(&mFallAccel_d, "FallAccel");
    getDynamicParam(&mFallAimSpeed_d, "FallAimSpeed");
    getDynamicParam(&mGravity_d, "Gravity");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mAtPoint_d, "AtPoint");
    getDynamicParam(&mAtRange_d, "AtRange");
    getDynamicParam(&mAtImpulse_d, "AtImpulse");
    getDynamicParam(&mAtImpact_d, "AtImpact");
    getDynamicParam(&mRelativeVel_d, "RelativeVel");
    getDynamicParam(&mAtAttr_d, "AtAttr");
    getStaticParam(&mFallSpeedRatioByRange_s, "FallSpeedRatioByRange");
    getDynamicParam(&mAtMinDamage_d, "AtMinDamage");
}

void ArrowShootMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
