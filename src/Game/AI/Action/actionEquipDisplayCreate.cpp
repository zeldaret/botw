#include "Game/AI/Action/actionEquipDisplayCreate.h"

namespace uking::action {

EquipDisplayCreate::EquipDisplayCreate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EquipDisplayCreate::~EquipDisplayCreate() = default;

bool EquipDisplayCreate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EquipDisplayCreate::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EquipDisplayCreate::leave_() {
    ksys::act::ai::Action::leave_();
}

void EquipDisplayCreate::loadParams_() {
    getStaticParam(&mDelayTimer_s, "DelayTimer");
    getStaticParam(&mSwordEquipNode_s, "SwordEquipNode");
    getStaticParam(&mLSwordEquipNode_s, "LSwordEquipNode");
    getStaticParam(&mSpearEquipNode_s, "SpearEquipNode");
    getStaticParam(&mBowEquipNode_s, "BowEquipNode");
    getStaticParam(&mShieldEquipNode_s, "ShieldEquipNode");
    getStaticParam(&mXLinkKey_s, "XLinkKey");
    getMapUnitParam(&mEquipStandSlot_m, "EquipStandSlot");
    getMapUnitParam(&mEquipStandNode_m, "EquipStandNode");
    getAITreeVariable(&mEquipDisplayChild_a, "EquipDisplayChild");
}

void EquipDisplayCreate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
