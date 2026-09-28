#include "Game/Actor/AI/aiGanonFlameBall.h"

namespace uking::ai {

GanonFlameBall::GanonFlameBall(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonFlameBall::~GanonFlameBall() = default;

bool GanonFlameBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonFlameBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonFlameBall::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonFlameBall::loadParams_() {
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
