#include "Game/AI/Action/actionSmallDamageDirectPreTargetBone.h"

namespace uking::action {

SmallDamageDirectPreTargetBone::SmallDamageDirectPreTargetBone(const InitArg& arg)
    : SmallDamage(arg) {}

SmallDamageDirectPreTargetBone::~SmallDamageDirectPreTargetBone() = default;

bool SmallDamageDirectPreTargetBone::init_(sead::Heap* heap) {
    return SmallDamage::init_(heap);
}

void SmallDamageDirectPreTargetBone::enter_(ksys::act::ai::InlineParamPack* params) {
    SmallDamage::enter_(params);
}

void SmallDamageDirectPreTargetBone::leave_() {
    SmallDamage::leave_();
}

void SmallDamageDirectPreTargetBone::loadParams_() {
    TakeHitImpactForce::loadParams_();
    getStaticParam(&mPreTargetBone_s, "PreTargetBone");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mIsSetHitPosSelecter_s, "IsSetHitPosSelecter");
}

void SmallDamageDirectPreTargetBone::calc_() {
    SmallDamage::calc_();
}

}  // namespace uking::action
