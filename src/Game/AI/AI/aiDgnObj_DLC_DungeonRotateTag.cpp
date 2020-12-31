#include "Game/AI/AI/aiDgnObj_DLC_DungeonRotateTag.h"

namespace uking::ai {

DgnObj_DLC_DungeonRotateTag::DgnObj_DLC_DungeonRotateTag(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

DgnObj_DLC_DungeonRotateTag::~DgnObj_DLC_DungeonRotateTag() = default;

bool DgnObj_DLC_DungeonRotateTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DgnObj_DLC_DungeonRotateTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DgnObj_DLC_DungeonRotateTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DgnObj_DLC_DungeonRotateTag::loadParams_() {
    getMapUnitParam(&mGearRatio_m, "GearRatio");
    getMapUnitParam(&mRegistFromBeginning_m, "RegistFromBeginning");
    getAITreeVariable(&mRotationOffset_a, "RotationOffset");
}

}  // namespace uking::ai
