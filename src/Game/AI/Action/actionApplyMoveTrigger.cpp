#include "Game/AI/Action/actionApplyMoveTrigger.h"

namespace uking::action {

ApplyMoveTrigger::ApplyMoveTrigger(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ApplyMoveTrigger::~ApplyMoveTrigger() = default;

bool ApplyMoveTrigger::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ApplyMoveTrigger::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ApplyMoveTrigger::leave_() {
    ksys::act::ai::Action::leave_();
}

void ApplyMoveTrigger::loadParams_() {
    getStaticParam(&mIsOnDebugDraw_s, "IsOnDebugDraw");
    getMapUnitParam(&mTriggerType_m, "TriggerType");
    getMapUnitParam(&mForceType_m, "ForceType");
    getMapUnitParam(&mApplyForceValue_m, "ApplyForceValue");
}

void ApplyMoveTrigger::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
