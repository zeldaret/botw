#include "Game/Actor/Action/actionFireBurnBase.h"

namespace uking::action {

FireBurnBase::FireBurnBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FireBurnBase::~FireBurnBase() = default;

bool FireBurnBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FireBurnBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FireBurnBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void FireBurnBase::loadParams_() {
    getStaticParam(&mChemicalRigidOn_s, "ChemicalRigidOn");
    getMapUnitParam(&mInitBurnState_m, "InitBurnState");
}

void FireBurnBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
