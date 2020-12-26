#include "Game/AI/Action/actionEquipDisplay.h"

namespace uking::action {

EquipDisplay::EquipDisplay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EquipDisplay::~EquipDisplay() = default;

bool EquipDisplay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EquipDisplay::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EquipDisplay::leave_() {
    ksys::act::ai::Action::leave_();
}

void EquipDisplay::loadParams_() {
    getStaticParam(&mSwordEquipNode_s, "SwordEquipNode");
    getStaticParam(&mLSwordEquipNode_s, "LSwordEquipNode");
    getStaticParam(&mSpearEquipNode_s, "SpearEquipNode");
    getStaticParam(&mBowEquipNode_s, "BowEquipNode");
    getStaticParam(&mShieldEquipNode_s, "ShieldEquipNode");
    getMapUnitParam(&mEquipStandSlot_m, "EquipStandSlot");
    getMapUnitParam(&mEquipStandNode_m, "EquipStandNode");
    getAITreeVariable(&mEquipDisplayChild_a, "EquipDisplayChild");
}

void EquipDisplay::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
