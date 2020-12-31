#include "Game/AI/AI/aiWaterSurfaceBase.h"

namespace uking::ai {

WaterSurfaceBase::WaterSurfaceBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WaterSurfaceBase::~WaterSurfaceBase() = default;

bool WaterSurfaceBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WaterSurfaceBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WaterSurfaceBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WaterSurfaceBase::loadParams_() {
    getMapUnitParam(&mFlowSpeedFactor_m, "FlowSpeedFactor");
}

}  // namespace uking::ai
