#include "Game/AI/Action/actionWaterSurfaceMove.h"

namespace uking::action {

WaterSurfaceMove::WaterSurfaceMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaterSurfaceMove::~WaterSurfaceMove() = default;

bool WaterSurfaceMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaterSurfaceMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaterSurfaceMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaterSurfaceMove::loadParams_() {
    getDynamicParam(&mSpeed_d, "Speed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void WaterSurfaceMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
