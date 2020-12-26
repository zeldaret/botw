#include "Game/AI/Action/actionSmallDamageDirectPreTargetBack.h"

namespace uking::action {

SmallDamageDirectPreTargetBack::SmallDamageDirectPreTargetBack(const InitArg& arg)
    : SmallDamageDirectPreTargetBone(arg) {}

SmallDamageDirectPreTargetBack::~SmallDamageDirectPreTargetBack() = default;

bool SmallDamageDirectPreTargetBack::init_(sead::Heap* heap) {
    return SmallDamageDirectPreTargetBone::init_(heap);
}

void SmallDamageDirectPreTargetBack::enter_(ksys::act::ai::InlineParamPack* params) {
    SmallDamageDirectPreTargetBone::enter_(params);
}

void SmallDamageDirectPreTargetBack::leave_() {
    SmallDamageDirectPreTargetBone::leave_();
}

void SmallDamageDirectPreTargetBack::loadParams_() {
    TakeHitImpactForce::loadParams_();
    getStaticParam(&mPreTargetBone_s, "PreTargetBone");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mIsSetHitPosSelecter_s, "IsSetHitPosSelecter");
}

void SmallDamageDirectPreTargetBack::calc_() {
    SmallDamageDirectPreTargetBone::calc_();
}

}  // namespace uking::action
