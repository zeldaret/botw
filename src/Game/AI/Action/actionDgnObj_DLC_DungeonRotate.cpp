#include "Game/AI/Action/actionDgnObj_DLC_DungeonRotate.h"

namespace uking::action {

DgnObj_DLC_DungeonRotate::DgnObj_DLC_DungeonRotate(const InitArg& arg) : DungeonRotateBase(arg) {}

DgnObj_DLC_DungeonRotate::~DgnObj_DLC_DungeonRotate() = default;

bool DgnObj_DLC_DungeonRotate::init_(sead::Heap* heap) {
    return DungeonRotateBase::init_(heap);
}

void DgnObj_DLC_DungeonRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateBase::enter_(params);
}

void DgnObj_DLC_DungeonRotate::leave_() {
    DungeonRotateBase::leave_();
}

void DgnObj_DLC_DungeonRotate::loadParams_() {
    DungeonRotateBase::loadParams_();
    getMapUnitParam(&mGearRatio_m, "GearRatio");
    getMapUnitParam(&mIsClockWiseRotation_m, "IsClockWiseRotation");
    getAITreeVariable(&mRotationOffset_a, "RotationOffset");
}

void DgnObj_DLC_DungeonRotate::calc_() {
    DungeonRotateBase::calc_();
}

}  // namespace uking::action
