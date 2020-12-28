#include "Game/AI/Action/actionSmallDamageDirectPreTargetBone.h"

namespace uking::action {

SmallDamageDirectPreTargetBone::SmallDamageDirectPreTargetBone(const InitArg& arg)
    : SmallDamage(arg) {}

SmallDamageDirectPreTargetBone::~SmallDamageDirectPreTargetBone() = default;

void SmallDamageDirectPreTargetBone::loadParams_() {
    TakeHitImpactForce::loadParams_();
    getStaticParam(&mPreTargetBone_s, "PreTargetBone");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mIsSetHitPosSelecter_s, "IsSetHitPosSelecter");
}

}  // namespace uking::action
