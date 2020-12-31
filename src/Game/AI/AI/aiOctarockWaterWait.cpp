#include "Game/AI/AI/aiOctarockWaterWait.h"

namespace uking::ai {

OctarockWaterWait::OctarockWaterWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OctarockWaterWait::~OctarockWaterWait() = default;

bool OctarockWaterWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OctarockWaterWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void OctarockWaterWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OctarockWaterWait::loadParams_() {
    getStaticParam(&mNoRiseTime_s, "NoRiseTime");
    getStaticParam(&mRiseDelayTimeMin_s, "RiseDelayTimeMin");
    getStaticParam(&mRiseDelayTimeMax_s, "RiseDelayTimeMax");
    getStaticParam(&mFinishFloatDelayTimeMin_s, "FinishFloatDelayTimeMin");
    getStaticParam(&mFinishFloatDelayTimeMax_s, "FinishFloatDelayTimeMax");
    getStaticParam(&mMinHeightFromWater_s, "MinHeightFromWater");
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

}  // namespace uking::ai
