#include "Game/Actor/Action/actionSwimSmallDamage.h"

namespace uking::action {

SwimSmallDamage::SwimSmallDamage(const InitArg& arg) : SmallDamage(arg) {}

SwimSmallDamage::~SwimSmallDamage() = default;

void SwimSmallDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    SmallDamage::enter_(params);
}

void SwimSmallDamage::leave_() {
    SmallDamage::leave_();
}

void SwimSmallDamage::loadParams_() {
    KnockBackHitImpactForce::loadParams_();
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatRadius_s, "FloatRadius");
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::action
