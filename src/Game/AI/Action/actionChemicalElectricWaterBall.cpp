#include "Game/AI/Action/actionChemicalElectricWaterBall.h"

namespace uking::action {

ChemicalElectricWaterBall::ChemicalElectricWaterBall(const InitArg& arg)
    : ChemicalAttackBall(arg) {}

ChemicalElectricWaterBall::~ChemicalElectricWaterBall() = default;

bool ChemicalElectricWaterBall::init_(sead::Heap* heap) {
    return ChemicalAttackBall::init_(heap);
}

void ChemicalElectricWaterBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalAttackBall::enter_(params);
}

void ChemicalElectricWaterBall::leave_() {
    ChemicalAttackBall::leave_();
}

void ChemicalElectricWaterBall::loadParams_() {
    ChemicalAttackBall::loadParams_();
    getStaticParam(&mDeleteTime_s, "DeleteTime");
    getStaticParam(&mTargetScale_s, "TargetScale");
    getStaticParam(&mScaleKeep_s, "ScaleKeep");
    getAITreeVariable(&mChemicalBulletBindActor_a, "ChemicalBulletBindActor");
}

void ChemicalElectricWaterBall::calc_() {
    ChemicalAttackBall::calc_();
}

}  // namespace uking::action
