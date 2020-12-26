#include "Game/AI/Action/actionApplyHorizontalImpulse.h"

namespace uking::action {

ApplyHorizontalImpulse::ApplyHorizontalImpulse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ApplyHorizontalImpulse::~ApplyHorizontalImpulse() = default;

bool ApplyHorizontalImpulse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ApplyHorizontalImpulse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ApplyHorizontalImpulse::leave_() {
    ksys::act::ai::Action::leave_();
}

void ApplyHorizontalImpulse::loadParams_() {
    getDynamicParam(&mDynVel_d, "DynVel");
    getDynamicParam(&mDynAngVel_d, "DynAngVel");
    getMapUnitParam(&mIsBreakable_m, "IsBreakable");
    getMapUnitParam(&mEnableToEmitSpEffect_m, "EnableToEmitSpEffect");
}

void ApplyHorizontalImpulse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
