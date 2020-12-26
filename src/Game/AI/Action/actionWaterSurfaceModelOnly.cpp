#include "Game/AI/Action/actionWaterSurfaceModelOnly.h"

namespace uking::action {

WaterSurfaceModelOnly::WaterSurfaceModelOnly(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaterSurfaceModelOnly::~WaterSurfaceModelOnly() = default;

bool WaterSurfaceModelOnly::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaterSurfaceModelOnly::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaterSurfaceModelOnly::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaterSurfaceModelOnly::loadParams_() {
    getMapUnitParam(&mFlowSpeedFactor_m, "FlowSpeedFactor");
}

void WaterSurfaceModelOnly::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
