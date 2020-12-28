#include "Game/AI/Action/actionRodMagicPhysBall.h"

namespace uking::action {

RodMagicPhysBall::RodMagicPhysBall(const InitArg& arg) : ChemicalPhysBall(arg) {}

RodMagicPhysBall::~RodMagicPhysBall() = default;

void RodMagicPhysBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalPhysBall::enter_(params);
}

void RodMagicPhysBall::leave_() {
    ChemicalPhysBall::leave_();
}

void RodMagicPhysBall::loadParams_() {
    ChemicalPhysBall::loadParams_();
    getStaticParam(&mCreateActorName_s, "CreateActorName");
    getStaticParam(&mChemicalType_s, "ChemicalType");
    getStaticParam(&mBgCheckHeight_s, "BgCheckHeight");
}

void RodMagicPhysBall::calc_() {
    ChemicalPhysBall::calc_();
}

}  // namespace uking::action
