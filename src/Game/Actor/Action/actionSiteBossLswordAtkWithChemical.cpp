#include "Game/Actor/Action/actionSiteBossLswordAtkWithChemical.h"

namespace uking::action {

SiteBossLswordAtkWithChemical::SiteBossLswordAtkWithChemical(const InitArg& arg)
    : SiteBossLswordAttack(arg) {}

SiteBossLswordAtkWithChemical::~SiteBossLswordAtkWithChemical() = default;

bool SiteBossLswordAtkWithChemical::init_(sead::Heap* heap) {
    return SiteBossLswordAttack::init_(heap);
}

void SiteBossLswordAtkWithChemical::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossLswordAttack::enter_(params);
}

void SiteBossLswordAtkWithChemical::leave_() {
    SiteBossLswordAttack::leave_();
}

void SiteBossLswordAtkWithChemical::loadParams_() {
    SiteBossLswordAttack::loadParams_();
    getStaticParam(&mEmitNum_s, "EmitNum");
    getStaticParam(&mEmitInterval_s, "EmitInterval");
    getStaticParam(&mEmitAttackDamage_s, "EmitAttackDamage");
    getStaticParam(&mEmitActorMinDamage_s, "EmitActorMinDamage");
    getStaticParam(&mEmitOffsetFromParent_s, "EmitOffsetFromParent");
    getStaticParam(&mEmitIntervalDist_s, "EmitIntervalDist");
    getStaticParam(&mEmitIntervalRotate_s, "EmitIntervalRotate");
    getStaticParam(&mEmitScale_s, "EmitScale");
    getStaticParam(&mEmitMaxScale_s, "EmitMaxScale");
    getStaticParam(&mScaleTime_s, "ScaleTime");
    getStaticParam(&mEmitStartFrame_s, "EmitStartFrame");
    getStaticParam(&mEmitAngleFromParent_s, "EmitAngleFromParent");
    getStaticParam(&mEmitActorSpeedRotate_s, "EmitActorSpeedRotate");
    getStaticParam(&mEmitActorName_s, "EmitActorName");
    getStaticParam(&mEmitPartsName_s, "EmitPartsName");
    getStaticParam(&mCallSEKeyAtAtOn_s, "CallSEKeyAtAtOn");
    getStaticParam(&mEmitActorSpeed_s, "EmitActorSpeed");
}

void SiteBossLswordAtkWithChemical::calc_() {
    SiteBossLswordAttack::calc_();
}

}  // namespace uking::action
