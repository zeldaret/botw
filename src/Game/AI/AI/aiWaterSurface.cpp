#include "Game/AI/AI/aiWaterSurface.h"

namespace uking::ai {

WaterSurface::WaterSurface(const InitArg& arg) : WaterSurfaceBase(arg) {}

WaterSurface::~WaterSurface() = default;

bool WaterSurface::init_(sead::Heap* heap) {
    return WaterSurfaceBase::init_(heap);
}

void WaterSurface::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterSurfaceBase::enter_(params);
}

void WaterSurface::leave_() {
    WaterSurfaceBase::leave_();
}

void WaterSurface::loadParams_() {
    WaterSurfaceBase::loadParams_();
    getStaticParam(&mLinkTagType_s, "LinkTagType");
    getMapUnitParam(&mRiseLength_m, "RiseLength");
    getMapUnitParam(&mRiseSpeed_m, "RiseSpeed");
}

}  // namespace uking::ai
