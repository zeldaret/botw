#include "Game/AI/AI/aiSnowBallNormal.h"

namespace uking::ai {

SnowBallNormal::SnowBallNormal(const InitArg& arg) : FixableLiftable(arg) {}

SnowBallNormal::~SnowBallNormal() = default;

bool SnowBallNormal::init_(sead::Heap* heap) {
    return FixableLiftable::init_(heap);
}

void SnowBallNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    FixableLiftable::enter_(params);
}

void SnowBallNormal::leave_() {
    FixableLiftable::leave_();
}

void SnowBallNormal::loadParams_() {
    FixableLiftable::loadParams_();
    getStaticParam(&mScaleRate_s, "ScaleRate");
    getStaticParam(&mScaleMax_s, "ScaleMax");
    getStaticParam(&mCarryScaleLimit_s, "CarryScaleLimit");
    getStaticParam(&mSendSignalLinearVelTh_s, "SendSignalLinearVelTh");
    getStaticParam(&mSendSignalScaleTh_s, "SendSignalScaleTh");
    getStaticParam(&mScaleMin_s, "ScaleMin");
    getStaticParam(&mDeleteUnderWaterDepth_s, "DeleteUnderWaterDepth");
    getStaticParam(&mMaxImpulseMassRate_s, "MaxImpulseMassRate");
    getStaticParam(&mAttReturnOnOffset_s, "AttReturnOnOffset");
    getStaticParam(&mScaleIncreaseDistance_s, "ScaleIncreaseDistance");
    getStaticParam(&mItemDropSetScaleOffset_s, "ItemDropSetScaleOffset");
    getStaticParam(&mItemDropDeleteScaleOffset_s, "ItemDropDeleteScaleOffset");
    getStaticParam(&mMinImpulseRatio_s, "MinImpulseRatio");
}

}  // namespace uking::ai
