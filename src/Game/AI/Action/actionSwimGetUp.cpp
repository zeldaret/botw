#include "Game/AI/Action/actionSwimGetUp.h"

namespace uking::action {

SwimGetUp::SwimGetUp(const InitArg& arg) : GetUp(arg) {}

SwimGetUp::~SwimGetUp() = default;

void SwimGetUp::enter_(ksys::act::ai::InlineParamPack* params) {
    GetUp::enter_(params);
}

void SwimGetUp::leave_() {
    GetUp::leave_();
}

void SwimGetUp::loadParams_() {
    GetUp::loadParams_();
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatRadius_s, "FloatRadius");
    getStaticParam(&mFloatCycleTime_s, "FloatCycleTime");
    getStaticParam(&mChangeDepthSpeed_s, "ChangeDepthSpeed");
    getStaticParam(&mUnderWaterDepth_s, "UnderWaterDepth");
}

void SwimGetUp::calc_() {
    GetUp::calc_();
}

}  // namespace uking::action
