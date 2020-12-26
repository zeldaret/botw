#include "Game/AI/Action/actionLookAtTarget.h"

namespace uking::action {

LookAtTarget::LookAtTarget(const InitArg& arg) : TurnBase(arg) {}

LookAtTarget::~LookAtTarget() = default;

bool LookAtTarget::init_(sead::Heap* heap) {
    return TurnBase::init_(heap);
}

void LookAtTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
}

void LookAtTarget::leave_() {
    TurnBase::leave_();
}

void LookAtTarget::loadParams_() {
    TurnBase::loadParams_();
    getStaticParam(&mASKeyName_s, "ASKeyName");
}

void LookAtTarget::calc_() {
    TurnBase::calc_();
}

}  // namespace uking::action
