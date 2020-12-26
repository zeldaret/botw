#include "Game/AI/Action/actionAnmDamage.h"

namespace uking::action {

AnmDamage::AnmDamage(const InitArg& arg) : SmallDamageBase(arg) {}

AnmDamage::~AnmDamage() = default;

bool AnmDamage::init_(sead::Heap* heap) {
    return SmallDamageBase::init_(heap);
}

void AnmDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    SmallDamageBase::enter_(params);
}

void AnmDamage::leave_() {
    SmallDamageBase::leave_();
}

void AnmDamage::loadParams_() {
    TakeHitImpactForce::loadParams_();
    getStaticParam(&mAS_s, "AS");
}

void AnmDamage::calc_() {
    SmallDamageBase::calc_();
}

}  // namespace uking::action
