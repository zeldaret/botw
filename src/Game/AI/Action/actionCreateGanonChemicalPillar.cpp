#include "Game/AI/Action/actionCreateGanonChemicalPillar.h"

namespace uking::action {

CreateGanonChemicalPillar::CreateGanonChemicalPillar(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CreateGanonChemicalPillar::~CreateGanonChemicalPillar() = default;

bool CreateGanonChemicalPillar::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CreateGanonChemicalPillar::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CreateGanonChemicalPillar::leave_() {
    ksys::act::ai::Action::leave_();
}

void CreateGanonChemicalPillar::loadParams_() {
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mScaleTime_s, "ScaleTime");
    getStaticParam(&mMaxScale_s, "MaxScale");
    getStaticParam(&mCreateActorName_s, "CreateActorName");
    getMapUnitParam(&mAddAtkPower_m, "AddAtkPower");
}

void CreateGanonChemicalPillar::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
