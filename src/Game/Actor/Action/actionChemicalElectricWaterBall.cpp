#include "Game/Actor/Action/actionChemicalElectricWaterBall.h"

namespace uking::action {

ChemicalElectricWaterBall::ChemicalElectricWaterBall(const InitArg& arg) : ChemicalAttack(arg) {}

ChemicalElectricWaterBall::~ChemicalElectricWaterBall() = default;

bool ChemicalElectricWaterBall::init_(sead::Heap* heap) {
    return ChemicalAttack::init_(heap);
}

void ChemicalElectricWaterBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalAttack::enter_(params);
}

void ChemicalElectricWaterBall::leave_() {
    ChemicalAttack::leave_();
}

void ChemicalElectricWaterBall::loadParams_() {
    ChemicalAttack::loadParams_();
    getStaticParam(&mDeleteTime_s, "DeleteTime");
    getStaticParam(&mTargetScale_s, "TargetScale");
    getStaticParam(&mScaleKeep_s, "ScaleKeep");
    getAITreeVariable(&mChemicalBulletBindActor_a, "ChemicalBulletBindActor");
}

void ChemicalElectricWaterBall::calc_() {
    ChemicalAttack::calc_();
}

}  // namespace uking::action
