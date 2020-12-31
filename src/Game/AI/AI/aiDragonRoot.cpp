#include "Game/AI/AI/aiDragonRoot.h"

namespace uking::ai {

DragonRoot::DragonRoot(const InitArg& arg) : DragonRootBase(arg) {}

DragonRoot::~DragonRoot() = default;

bool DragonRoot::init_(sead::Heap* heap) {
    return DragonRootBase::init_(heap);
}

void DragonRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    DragonRootBase::enter_(params);
}

void DragonRoot::leave_() {
    DragonRootBase::leave_();
}

void DragonRoot::loadParams_() {
    DragonRootBase::loadParams_();
    getStaticParam(&mChemicalBulletRate_s, "ChemicalBulletRate");
    getStaticParam(&mChemicalBulletNum_s, "ChemicalBulletNum");
    getStaticParam(&mUpdraftInterval_s, "UpdraftInterval");
    getStaticParam(&mReturnTime_s, "ReturnTime");
    getStaticParam(&mBodyHitDamage_s, "BodyHitDamage");
    getStaticParam(&mBodyHitPower_s, "BodyHitPower");
    getStaticParam(&mBodyHitImpact_s, "BodyHitImpact");
    getStaticParam(&mBodyHitShieldDamage_s, "BodyHitShieldDamage");
    getStaticParam(&mOnRailDistance_s, "OnRailDistance");
    getStaticParam(&mFarDistance_s, "FarDistance");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mChemicalBulletArea_s, "ChemicalBulletArea");
    getStaticParam(&mChemicalWindArea_s, "ChemicalWindArea");
    getStaticParam(&mChemicalWindPower_s, "ChemicalWindPower");
    getStaticParam(&mChemicalWindLimitHeight_s, "ChemicalWindLimitHeight");
    getStaticParam(&mUpdraftPower_s, "UpdraftPower");
    getStaticParam(&mUpdraftTime_s, "UpdraftTime");
    getStaticParam(&mUpdraftBoost_s, "UpdraftBoost");
    getStaticParam(&mInitBackRailDistance_s, "InitBackRailDistance");
    getStaticParam(&mIsEmitChemical_s, "IsEmitChemical");
    getStaticParam(&mCommonTableName_s, "CommonTableName");
    getStaticParam(&mTsunoTableName_s, "TsunoTableName");
    getStaticParam(&mTsumeTableName_s, "TsumeTableName");
    getStaticParam(&mKibaTableName_s, "KibaTableName");
    getStaticParam(&mChemicalBulletActor_s, "ChemicalBulletActor");
    getStaticParam(&mDefaultMaterialAnmName_s, "DefaultMaterialAnmName");
    getStaticParam(&mHornAnmName_s, "HornAnmName");
    getAITreeVariable(&mCreateRailName_a, "CreateRailName");
}

}  // namespace uking::ai
