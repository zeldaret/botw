#include "Game/AI/Action/actionEquipedRod.h"

namespace uking::action {

EquipedRod::EquipedRod(const InitArg& arg) : EquipedAction(arg) {}

EquipedRod::~EquipedRod() = default;

void EquipedRod::enter_(ksys::act::ai::InlineParamPack* params) {
    EquipedAction::enter_(params);
}

void EquipedRod::leave_() {
    EquipedAction::leave_();
}

void EquipedRod::loadParams_() {
    EquipedAction::loadParams_();
    getStaticParam(&mMagicCreateYOffset_s, "MagicCreateYOffset");
    getStaticParam(&mMagicShootVelOffset_s, "MagicShootVelOffset");
    getStaticParam(&mIsAxisYTop_s, "IsAxisYTop");
    getStaticParam(&mIsCreateWeaponPosOffset_s, "IsCreateWeaponPosOffset");
    getStaticParam(&mCreatePosOffset_s, "CreatePosOffset");
    getStaticParam(&mAxisYAngle_s, "AxisYAngle");
    getAITreeVariable(&mMagicCreateUnit_a, "MagicCreateUnit");
}

void EquipedRod::calc_() {
    EquipedAction::calc_();
}

}  // namespace uking::action
