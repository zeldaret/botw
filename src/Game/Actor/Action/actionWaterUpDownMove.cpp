#include "Game/Actor/Action/actionWaterUpDownMove.h"

namespace uking::action {

WaterUpDownMove::WaterUpDownMove(const InitArg& arg) : WaterDepthMoveBase(arg) {}

WaterUpDownMove::~WaterUpDownMove() = default;

bool WaterUpDownMove::init_(sead::Heap* heap) {
    return WaterDepthMoveBase::init_(heap);
}

void WaterUpDownMove::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterDepthMoveBase::enter_(params);
}

void WaterUpDownMove::leave_() {
    WaterDepthMoveBase::leave_();
}

void WaterUpDownMove::loadParams_() {
    WaterDepthMoveBase::loadParams_();
    getStaticParam(&mStartDepth_s, "StartDepth");
    getStaticParam(&mTargetDepth_s, "TargetDepth");
}

void WaterUpDownMove::calc_() {
    WaterDepthMoveBase::calc_();
}

}  // namespace uking::action
