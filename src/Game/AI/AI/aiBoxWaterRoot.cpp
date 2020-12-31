#include "Game/AI/AI/aiBoxWaterRoot.h"

namespace uking::ai {

BoxWaterRoot::BoxWaterRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BoxWaterRoot::~BoxWaterRoot() = default;

bool BoxWaterRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BoxWaterRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BoxWaterRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BoxWaterRoot::loadParams_() {
    getMapUnitParam(&mWaterMaterial_m, "WaterMaterial");
    getMapUnitParam(&mFlowSpeedFactor_m, "FlowSpeedFactor");
    getMapUnitParam(&mWaterfallRadius_m, "WaterfallRadius");
    getMapUnitParam(&mWaterfallLength_m, "WaterfallLength");
    getMapUnitParam(&mWaterfallThickness_m, "WaterfallThickness");
    getMapUnitParam(&mWaterfallAngle_m, "WaterfallAngle");
    getMapUnitParam(&mSoundInDoorType_m, "SoundInDoorType");
}

}  // namespace uking::ai
