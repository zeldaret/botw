#include "Game/AI/Action/actionExpandChemicalField.h"

namespace uking::action {

ExpandChemicalField::ExpandChemicalField(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ExpandChemicalField::~ExpandChemicalField() = default;

bool ExpandChemicalField::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ExpandChemicalField::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ExpandChemicalField::leave_() {
    ksys::act::ai::Action::leave_();
}

void ExpandChemicalField::loadParams_() {
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackAttr_m, "AttackAttr");
    getMapUnitParam(&mAttackType_m, "AttackType");
    getMapUnitParam(&mCutGrassType_m, "CutGrassType");
    getMapUnitParam(&mAttackTarget_m, "AttackTarget");
    getMapUnitParam(&mAttackDirType_m, "AttackDirType");
    getMapUnitParam(&mScaleTime_m, "ScaleTime");
    getMapUnitParam(&mIsReuseActor_m, "IsReuseActor");
    getMapUnitParam(&mIsUseAtCollision_m, "IsUseAtCollision");
    getMapUnitParam(&mXLinkKey_m, "XLinkKey");
}

void ExpandChemicalField::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
