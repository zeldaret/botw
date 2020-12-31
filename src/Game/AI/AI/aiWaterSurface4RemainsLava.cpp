#include "Game/AI/AI/aiWaterSurface4RemainsLava.h"

namespace uking::ai {

WaterSurface4RemainsLava::WaterSurface4RemainsLava(const InitArg& arg) : WaterSurface(arg) {}

WaterSurface4RemainsLava::~WaterSurface4RemainsLava() = default;

bool WaterSurface4RemainsLava::init_(sead::Heap* heap) {
    return WaterSurface::init_(heap);
}

void WaterSurface4RemainsLava::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterSurface::enter_(params);
}

void WaterSurface4RemainsLava::leave_() {
    WaterSurface::leave_();
}

void WaterSurface4RemainsLava::loadParams_() {
    WaterSurface::loadParams_();
}

}  // namespace uking::ai
