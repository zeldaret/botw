#include "Game/AI/Action/actionDgnObj_DLC_CogWheel_Rotate.h"

namespace uking::action {

DgnObj_DLC_CogWheel_Rotate::DgnObj_DLC_CogWheel_Rotate(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DgnObj_DLC_CogWheel_Rotate::~DgnObj_DLC_CogWheel_Rotate() = default;

bool DgnObj_DLC_CogWheel_Rotate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DgnObj_DLC_CogWheel_Rotate::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DgnObj_DLC_CogWheel_Rotate::leave_() {
    ksys::act::ai::Action::leave_();
}

void DgnObj_DLC_CogWheel_Rotate::loadParams_() {
    getStaticParam(&mTargetAngularDisplPerSec_s, "TargetAngularDisplPerSec");
    getDynamicParam(&mIsRegisteredFrame_d, "IsRegisteredFrame");
    getMapUnitParam(&mGearRatio_m, "GearRatio");
    getMapUnitParam(&mIsClockWiseRotation_m, "IsClockWiseRotation");
    getAITreeVariable(&mRotationOffset_a, "RotationOffset");
}

void DgnObj_DLC_CogWheel_Rotate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
