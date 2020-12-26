#include "Game/AI/Action/actionRotateTurnToTarget.h"

namespace uking::action {

RotateTurnToTarget::RotateTurnToTarget(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RotateTurnToTarget::~RotateTurnToTarget() = default;

bool RotateTurnToTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RotateTurnToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RotateTurnToTarget::leave_() {
    ksys::act::ai::Action::leave_();
}

void RotateTurnToTarget::loadParams_() {
    getStaticParam(&mAngSpd_s, "AngSpd");
    getStaticParam(&mIsJumpType_s, "IsJumpType");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
}

void RotateTurnToTarget::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
