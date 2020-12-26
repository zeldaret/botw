#include "Game/AI/Action/actionCapturedActKnockBack.h"

namespace uking::action {

CapturedActKnockBack::CapturedActKnockBack(const InitArg& arg) : SmallDamageBase(arg) {}

CapturedActKnockBack::~CapturedActKnockBack() = default;

bool CapturedActKnockBack::init_(sead::Heap* heap) {
    return SmallDamageBase::init_(heap);
}

void CapturedActKnockBack::enter_(ksys::act::ai::InlineParamPack* params) {
    SmallDamageBase::enter_(params);
}

void CapturedActKnockBack::leave_() {
    SmallDamageBase::leave_();
}

void CapturedActKnockBack::loadParams_() {
    TakeHitImpactForce::loadParams_();
}

void CapturedActKnockBack::calc_() {
    SmallDamageBase::calc_();
}

}  // namespace uking::action
