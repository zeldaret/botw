#include "Game/AI/Action/actionGanonSmallDamage.h"

namespace uking::action {

GanonSmallDamage::GanonSmallDamage(const InitArg& arg) : SmallDamageBase(arg) {}

GanonSmallDamage::~GanonSmallDamage() = default;

bool GanonSmallDamage::init_(sead::Heap* heap) {
    return SmallDamageBase::init_(heap);
}

void GanonSmallDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    SmallDamageBase::enter_(params);
}

void GanonSmallDamage::leave_() {
    SmallDamageBase::leave_();
}

void GanonSmallDamage::loadParams_() {
    TakeHitImpactForce::loadParams_();
    getStaticParam(&mUpAS_s, "UpAS");
    getStaticParam(&mAS_s, "AS");
}

void GanonSmallDamage::calc_() {
    SmallDamageBase::calc_();
}

}  // namespace uking::action
