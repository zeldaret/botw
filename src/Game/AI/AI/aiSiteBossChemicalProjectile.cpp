#include "Game/AI/AI/aiSiteBossChemicalProjectile.h"

namespace uking::ai {

SiteBossChemicalProjectile::SiteBossChemicalProjectile(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SiteBossChemicalProjectile::~SiteBossChemicalProjectile() = default;

bool SiteBossChemicalProjectile::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossChemicalProjectile::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossChemicalProjectile::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossChemicalProjectile::loadParams_() {
    getStaticParam(&mExplosionTime_s, "ExplosionTime");
    getStaticParam(&mChaseAngleLimit_s, "ChaseAngleLimit");
    getStaticParam(&mReflectSpeedRate_s, "ReflectSpeedRate");
    getStaticParam(&mIsForceDelete_s, "IsForceDelete");
    getStaticParam(&mIsAdjustHeight_s, "IsAdjustHeight");
    getStaticParam(&mIsSetParentSystemGroupHandler_s, "IsSetParentSystemGroupHandler");
    getStaticParam(&mIsSetBindSpeed_s, "IsSetBindSpeed");
    getStaticParam(&mIsIgnoreObject_s, "IsIgnoreObject");
    getStaticParam(&mBindNodeName_s, "BindNodeName");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAtMinDamage_m, "AtMinDamage");
    getMapUnitParam(&mScaleTime_m, "ScaleTime");
    getMapUnitParam(&mRange_m, "Range");
    getMapUnitParam(&mAtkRadiusMax_m, "AtkRadiusMax");
}

}  // namespace uking::ai
