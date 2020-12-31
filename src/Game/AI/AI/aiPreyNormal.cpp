#include "Game/AI/AI/aiPreyNormal.h"

namespace uking::ai {

PreyNormal::PreyNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyNormal::~PreyNormal() = default;

bool PreyNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PreyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PreyNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PreyNormal::loadParams_() {
    getStaticParam(&mChangeBattleStateRadius_s, "ChangeBattleStateRadius");
    getStaticParam(&mCounterAttackRadius_s, "CounterAttackRadius");
    getStaticParam(&mCounterAttackRate_s, "CounterAttackRate");
    getStaticParam(&mAddCautionLevelVal_s, "AddCautionLevelVal");
    getStaticParam(&mAutoReduceCautionLevelVal_s, "AutoReduceCautionLevelVal");
    getStaticParam(&mLimitOverReduceCautionLevelVal_s, "LimitOverReduceCautionLevelVal");
    getStaticParam(&mAwnRangeScaleWhenAttention_s, "AwnRangeScaleWhenAttention");
    getStaticParam(&mTargetLostTime_s, "TargetLostTime");
    getStaticParam(&mAllowRoarRadius_s, "AllowRoarRadius");
    getStaticParam(&mEscapeWaterFlowLimit_s, "EscapeWaterFlowLimit");
    getStaticParam(&mNewFoodAddTime_s, "NewFoodAddTime");
    getStaticParam(&mIsUseEscapeState_s, "IsUseEscapeState");
    getStaticParam(&mIsPositiveAttacker_s, "IsPositiveAttacker");
    getStaticParam(&mIsSearchTarget_s, "IsSearchTarget");
    getStaticParam(&mIsEmitForceEscapeSignal_s, "IsEmitForceEscapeSignal");
    getStaticParam(&mIsReceivedForceEscapeSignal_s, "IsReceivedForceEscapeSignal");
    getStaticParam(&mIsCheckSandStorm_s, "IsCheckSandStorm");
    getMapUnitParam(&mIsLocatorCreate_m, "IsLocatorCreate");
    getMapUnitParam(&mEnableNoEntryAreaCheck_m, "EnableNoEntryAreaCheck");
}

}  // namespace uking::ai
