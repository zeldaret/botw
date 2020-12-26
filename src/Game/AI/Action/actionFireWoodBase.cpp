#include "Game/AI/Action/actionFireWoodBase.h"

namespace uking::action {

FireWoodBase::FireWoodBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FireWoodBase::~FireWoodBase() = default;

bool FireWoodBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FireWoodBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FireWoodBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void FireWoodBase::loadParams_() {
    getStaticParam(&mChemicalRigidOn_s, "ChemicalRigidOn");
    getMapUnitParam(&mInitBurnState_m, "InitBurnState");
}

void FireWoodBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
