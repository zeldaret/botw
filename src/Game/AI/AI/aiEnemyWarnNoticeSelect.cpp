#include "Game/AI/AI/aiEnemyWarnNoticeSelect.h"

namespace uking::ai {

EnemyWarnNoticeSelect::EnemyWarnNoticeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyWarnNoticeSelect::~EnemyWarnNoticeSelect() = default;

bool EnemyWarnNoticeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyWarnNoticeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyWarnNoticeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyWarnNoticeSelect::loadParams_() {
    getStaticParam(&mWarnNoticeTime_s, "WarnNoticeTime");
    getStaticParam(&mWarnNoticeTimeRnd_s, "WarnNoticeTimeRnd");
    getStaticParam(&mWarnBlinkTime_s, "WarnBlinkTime");
    getStaticParam(&mLostCounter_s, "LostCounter");
    getStaticParam(&mIsSight_s, "IsSight");
    getStaticParam(&mIsWorry_s, "IsWorry");
    getDynamicParam(&mForceNotice_d, "ForceNotice");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getStaticParam(&mPenaltyStair2Num_s, "PenaltyStair2Num");
    getStaticParam(&mMaxCountUp_s, "MaxCountUp");
    getStaticParam(&mPenalty_s, "Penalty");
    getStaticParam(&mNoPenaltyNum_s, "NoPenaltyNum");
    getAITreeVariable(&mIsTrgChangeUnderWaterState_a, "IsTrgChangeUnderWaterState");
}

}  // namespace uking::ai
