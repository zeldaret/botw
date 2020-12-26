#include "Game/AI/Action/actionChemicalPhysHitBreakBall.h"

namespace uking::action {

ChemicalPhysHitBreakBall::ChemicalPhysHitBreakBall(const InitArg& arg) : ChemicalPhysBall(arg) {}

ChemicalPhysHitBreakBall::~ChemicalPhysHitBreakBall() = default;

bool ChemicalPhysHitBreakBall::init_(sead::Heap* heap) {
    return ChemicalPhysBall::init_(heap);
}

void ChemicalPhysHitBreakBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalPhysBall::enter_(params);
}

void ChemicalPhysHitBreakBall::leave_() {
    ChemicalPhysBall::leave_();
}

void ChemicalPhysHitBreakBall::loadParams_() {
    ChemicalAttackBall::loadParams_();
    getStaticParam(&mDeleteTime_s, "DeleteTime");
}

void ChemicalPhysHitBreakBall::calc_() {
    ChemicalPhysBall::calc_();
}

}  // namespace uking::action
