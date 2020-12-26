#include "Game/AI/Action/actionTargetCircleSwim.h"

namespace uking::action {

TargetCircleSwim::TargetCircleSwim(const InitArg& arg) : TargetCircle(arg) {}

TargetCircleSwim::~TargetCircleSwim() = default;

bool TargetCircleSwim::init_(sead::Heap* heap) {
    return TargetCircle::init_(heap);
}

void TargetCircleSwim::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetCircle::enter_(params);
}

void TargetCircleSwim::leave_() {
    TargetCircle::leave_();
}

void TargetCircleSwim::loadParams_() {
    TargetCircle::loadParams_();
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatRadius_s, "FloatRadius");
    getStaticParam(&mFloatCycleTime_s, "FloatCycleTime");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mChangeDepthSpeed_s, "ChangeDepthSpeed");
}

void TargetCircleSwim::calc_() {
    TargetCircle::calc_();
}

}  // namespace uking::action
