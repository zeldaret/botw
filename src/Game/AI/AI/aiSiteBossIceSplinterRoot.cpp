#include "Game/AI/AI/aiSiteBossIceSplinterRoot.h"

namespace uking::ai {

SiteBossIceSplinterRoot::SiteBossIceSplinterRoot(const InitArg& arg)
    : SiteBossChemicalProjectile(arg) {}

SiteBossIceSplinterRoot::~SiteBossIceSplinterRoot() = default;

bool SiteBossIceSplinterRoot::init_(sead::Heap* heap) {
    return SiteBossChemicalProjectile::init_(heap);
}

void SiteBossIceSplinterRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossChemicalProjectile::enter_(params);
}

void SiteBossIceSplinterRoot::leave_() {
    SiteBossChemicalProjectile::leave_();
}

void SiteBossIceSplinterRoot::loadParams_() {
    SiteBossChemicalProjectile::loadParams_();
    getStaticParam(&mReflectAtkPower_s, "ReflectAtkPower");
    getStaticParam(&mChaseAngleMin_s, "ChaseAngleMin");
    getStaticParam(&mRotateSpeed_s, "RotateSpeed");
    getStaticParam(&mBindNodeName0_s, "BindNodeName0");
    getStaticParam(&mBindNodeName1_s, "BindNodeName1");
    getStaticParam(&mChaseParentNode_s, "ChaseParentNode");
    getStaticParam(&mBindOffset0_s, "BindOffset0");
    getStaticParam(&mBindOffset1_s, "BindOffset1");
    getStaticParam(&mBindOffset2_s, "BindOffset2");
    getStaticParam(&mBindOffset3_s, "BindOffset3");
    getStaticParam(&mBindOffset4_s, "BindOffset4");
    getStaticParam(&mBindOffset5_s, "BindOffset5");
    getStaticParam(&mBindOffset6_s, "BindOffset6");
    getStaticParam(&mBindOffset7_s, "BindOffset7");
    getStaticParam(&mBindOffset8_s, "BindOffset8");
    getStaticParam(&mRotateSpeedAtHit_s, "RotateSpeedAtHit");
    getStaticParam(&mRotateSpeedAtFall_s, "RotateSpeedAtFall");
    getMapUnitParam(&mCount_m, "Count");
}

}  // namespace uking::ai
