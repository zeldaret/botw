#include "Game/AI/AI/aiCircleMoveInFluid.h"

namespace uking::ai {

CircleMoveInFluid::CircleMoveInFluid(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CircleMoveInFluid::~CircleMoveInFluid() = default;

bool CircleMoveInFluid::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CircleMoveInFluid::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CircleMoveInFluid::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CircleMoveInFluid::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRadiusX_s, "RadiusX");
    getStaticParam(&mRadiusZ_s, "RadiusZ");
    getStaticParam(&mMinRandRadiusRate_s, "MinRandRadiusRate");
    getStaticParam(&mMaxRandRadiusRate_s, "MaxRandRadiusRate");
    getStaticParam(&mAddAngleRateX_s, "AddAngleRateX");
    getStaticParam(&mAddAngleRateZ_s, "AddAngleRateZ");
    getStaticParam(&mRandRangeY_s, "RandRangeY");
    getStaticParam(&mRandRangeYOffest_s, "RandRangeYOffest");
    getStaticParam(&mLimitSpeedMoveY_s, "LimitSpeedMoveY");
    getStaticParam(&mChangeInterval_s, "ChangeInterval");
    getStaticParam(&mRandChangeInterval_s, "RandChangeInterval");
    getStaticParam(&mReverseMoveRate_s, "ReverseMoveRate");
    getStaticParam(&mIsSetSystemDeleteDistance_s, "IsSetSystemDeleteDistance");
}

}  // namespace uking::ai
