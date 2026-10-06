#include "Game/Actor/Action/actionASPlayRotateTurnToTarget.h"

namespace uking::action {

ASPlayRotateTurnToTarget::ASPlayRotateTurnToTarget(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ASPlayRotateTurnToTarget::~ASPlayRotateTurnToTarget() = default;

bool ASPlayRotateTurnToTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ASPlayRotateTurnToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ASPlayRotateTurnToTarget::leave_() {
    ksys::act::ai::Action::leave_();
}

void ASPlayRotateTurnToTarget::loadParams_() {
    getStaticParam(&mAngSpd_s, "AngSpd");
    getStaticParam(&mIsJumpType_s, "IsJumpType");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
}

void ASPlayRotateTurnToTarget::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
