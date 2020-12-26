#include "Game/AI/Action/actionWaterUpDownAnmDrivenMove.h"

namespace uking::action {

WaterUpDownAnmDrivenMove::WaterUpDownAnmDrivenMove(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

WaterUpDownAnmDrivenMove::~WaterUpDownAnmDrivenMove() = default;

bool WaterUpDownAnmDrivenMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaterUpDownAnmDrivenMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaterUpDownAnmDrivenMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaterUpDownAnmDrivenMove::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mTargetDepth_s, "TargetDepth");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mASName_s, "ASName");
}

void WaterUpDownAnmDrivenMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
