#include "Game/AI/AI/aiSiteBossFlameBall.h"

namespace uking::ai {

SiteBossFlameBall::SiteBossFlameBall(const InitArg& arg) : SiteBossChemicalProjectile(arg) {}

SiteBossFlameBall::~SiteBossFlameBall() = default;

bool SiteBossFlameBall::init_(sead::Heap* heap) {
    return SiteBossChemicalProjectile::init_(heap);
}

void SiteBossFlameBall::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossChemicalProjectile::enter_(params);
}

void SiteBossFlameBall::leave_() {
    SiteBossChemicalProjectile::leave_();
}

void SiteBossFlameBall::loadParams_() {
    SiteBossChemicalProjectile::loadParams_();
    getStaticParam(&mChemicalIndex_s, "ChemicalIndex");
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mMoveOffset_s, "MoveOffset");
    getStaticParam(&mCountOffset_s, "CountOffset");
    getStaticParam(&mIsInfluence_s, "IsInfluence");
    getMapUnitParam(&mCount_m, "Count");
    getMapUnitParam(&mPosOffset_m, "PosOffset");
}

}  // namespace uking::ai
