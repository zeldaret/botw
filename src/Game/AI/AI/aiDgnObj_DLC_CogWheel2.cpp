#include "Game/AI/AI/aiDgnObj_DLC_CogWheel2.h"

namespace uking::ai {

DgnObj_DLC_CogWheel2::DgnObj_DLC_CogWheel2(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DgnObj_DLC_CogWheel2::~DgnObj_DLC_CogWheel2() = default;

bool DgnObj_DLC_CogWheel2::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DgnObj_DLC_CogWheel2::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DgnObj_DLC_CogWheel2::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DgnObj_DLC_CogWheel2::loadParams_() {
    getStaticParam(&mCorrectConstraint_s, "CorrectConstraint");
    getMapUnitParam(&mGearRatio_m, "GearRatio");
    getMapUnitParam(&mRegistFromBeginning_m, "RegistFromBeginning");
    getMapUnitParam(&mJoinSystemGroup_m, "JoinSystemGroup");
    getAITreeVariable(&mRotationOffset_a, "RotationOffset");
}

}  // namespace uking::ai
